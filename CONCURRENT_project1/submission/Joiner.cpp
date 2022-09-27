#include "Joiner.hpp"
#include <cassert>
#include <iostream>
#include <string>
#include <unordered_map>
#include <utility>
#include <set>
#include <sstream>
#include <vector>
#include "Parser.hpp"

//---------------------------------------------------------------------------
using namespace std;
//---------------------------------------------------------------------------
void Joiner::addRelation(const char* fileName)
// Loads a relation from disk
{
  relations.emplace_back(fileName);
}
//---------------------------------------------------------------------------
Relation& Joiner::getRelation(unsigned relationId)
// Loads a relation from disk
{
  if (relationId >= relations.size()) {
    cerr << "Relation with id: " << relationId << " does not exist" << endl;
    throw;
  }
  return relations[relationId];
}
//---------------------------------------------------------------------------
unique_ptr<Operator> Joiner::addScan(set<unsigned>& usedRelations,SelectInfo& info,QueryInfo& query)
  // Add scan to query
{
  usedRelations.emplace(info.binding);
  vector<FilterInfo> filters;
    for (auto& f : query.filters) {
      if (f.filterColumn.binding==info.binding) {
        filters.emplace_back(f);
      }
    }
  return filters.size()?make_unique<FilterScan>(getRelation(info.relId),filters,this->col_info[info.binding]):make_unique<Scan>(getRelation(info.relId),info.binding,this->col_info[info.binding]);
}
//---------------------------------------------------------------------------
enum QueryGraphProvides {  Left, Right, Both, None };
//---------------------------------------------------------------------------
static QueryGraphProvides analyzeInputOfJoin(set<unsigned>& usedRelations,SelectInfo& leftInfo,SelectInfo& rightInfo)
  // Analyzes inputs of join
{
  bool usedLeft=usedRelations.count(leftInfo.binding);
  bool usedRight=usedRelations.count(rightInfo.binding);

  if (usedLeft^usedRight)
    return usedLeft?QueryGraphProvides::Left:QueryGraphProvides::Right;
  if (usedLeft&&usedRight)
    return QueryGraphProvides::Both;
  return QueryGraphProvides::None;
}
//---------------------------------------------------------------------------
string Joiner::join(QueryInfo& query)
  // Executes a join query
{
  // relation(table) informations are stored in joiner::relation already.
  // we can access element relations[relId].columns[colId][cId]
  // we can get total number of tuple relations[relId].size
  // we can get numbers of columns relations[relId].numColumns

  // get all column id we will use.
  // use <PredicateInfo>query.predicates,<FilterInfo>query.filters -> <SelectInfo> relId,binding,colId
  int sz  = relations.size();
  set<unsigned>  col_info[sz];
  //col_info.insert(1);
    for (auto& f : query.filters) {
        col_info[f.filterColumn.binding].emplace(f.filterColumn.colId);
    }
    for (auto& f : query.predicates) {
        col_info[f.left.binding].emplace(f.left.colId);
        col_info[f.right.binding].emplace(f.right.colId);
    }
    for (auto& f : query.selections) {
        col_info[f.binding].emplace(f.colId);
        col_info[f.binding].emplace(f.colId);
    }
  this->col_info = col_info;
  //cerr << query.dumpText() << endl;
    set<unsigned> usedRelations;

   // we have to reorganize query.predicates before joining process

  // We always start with the first join predicate and append the other joins to it (--> left-deep join trees)
  // You might want to choose a smarter join ordering ...
  auto& firstJoin=query.predicates[0];
  auto left=addScan(usedRelations,firstJoin.left,query);
  auto right=addScan(usedRelations,firstJoin.right,query);
  unique_ptr<Operator> root=make_unique<Join>(move(left),move(right),firstJoin);



  for (unsigned i=1;i<query.predicates.size();++i) {
    auto& pInfo=query.predicates[i];
    auto& leftInfo=pInfo.left; auto& rightInfo=pInfo.right;
    unique_ptr<Operator> left, right;
    switch(analyzeInputOfJoin(usedRelations,leftInfo,rightInfo)) {
      case QueryGraphProvides::Left:
        left=move(root);
        right=addScan(usedRelations,rightInfo,query);
        root=make_unique<Join>(move(left),move(right),pInfo);
        break;
      case QueryGraphProvides::Right:
        left=addScan(usedRelations,leftInfo,query);
        right=move(root);
        root=make_unique<Join>(move(left),move(right),pInfo);
        break;
      case QueryGraphProvides::Both:
        // All relations of this join are already used somewhere else in the query.
        // Thus, we have either a cycle in our join graph or more than one join predicate per join.
        root=make_unique<SelfJoin>(move(root),pInfo);
        break;
      case QueryGraphProvides::None:
        // Process this predicate later when we can connect it to the other joins
        // We never have cross products
        query.predicates.push_back(pInfo);
        break;
    };
  }


  Checksum checkSum(move(root),query.selections);
  checkSum.run();


  stringstream out;
  auto& results=checkSum.checkSums;
  for (unsigned i=0;i<results.size();++i) {
    out << (checkSum.resultSize==0?"NULL":to_string(results[i]));
    if (i<results.size()-1)
      out << " ";
  }
  out << "\n";
  return out.str();
}
//---------------------------------------------------------------------------
