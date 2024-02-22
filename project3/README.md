## BackGround
#### Bw+tree
Bw-tree는 B-tree와 Write-Ahead의 약자로, 고성능 동시성과 낮은 지연 시간이 요구되는 데이터베이스 및 파일 시스템용으로 설계된 데이터 구조이다. B-tree의 변형으로, 비휘발성 메모리를 사용하는 시스템이나 효율적인 락-프리(lock-free) 작업이 필요한 시나리오에 최적화되어 있다.

Bw-tree는 여러 주요 특성을 통해 높은 성능과 동시성을 달성한다:

래치-프리(Latch-free) 설계: 전통적인 잠금 대신, 원자적 연산을 사용하여 동시성을 관리하여, 멀티 스레드 환경에서의 오버헤드와 잠재적인 병목 현상을 줄인다.

델타 노드 (delta-node): 변경 사항을 기록하는 데 사용되며, 이는 기본 구조의 변경 없이도 업데이트를 효율적으로 수행할 수 있게 한다.

이러한 특성 덕분에 Bw-tree는 인 메모리 데이터베이스와 같이 높은 동시성과 낮은 지연 시간을 필요로 하는 작업에 적합하다.

## Problem Definition
#### Problem situation
수천 명의 사용자가 특정 좌석에 액세스하는 콘서트 티켓팅과 같이 특정 핵심 정보를 집중적으로 수정해야 하는 서비스에서는 만족스러운 사용자 경험을 위해 응답 시간이 매우 중요하다. 하지만, 기존의 Bw+tree의 경우, 좁은 영역의 키에 많은 량의 요청이 발생하였을 때, 성능이 하락하는 문제가 존재한다. 이 문제는 [표-1]에서 명백히 나타나며, 연속된 64개 key 범위에서 혼잡이 발생할 경우 응답 시간이 크게 지연되는 것을 볼 수 있다.
![image](https://user-images.githubusercontent.com/96645965/216049878-15744ca6-9f01-40a6-a94e-8281c5cc9879.png)
[Table-1]
#### [Table-1] analysis
이 표는 bw-tree가 좁은 키 범위에서 대량의 수정을 처리할 수 있는 능력을 검토한 실험 결과이다. 1,024x1,024 요소를 가진 bw-tree를 생성하고, 20개의 스레드가 1,024x1,024번 주어진 작업을 시도한다. 작업은 범위 내의 임의의 키에 대하여, 해당 키를 가진 요소를 삭제한 다음 삽입한다. 이러한 작업의 총 소요 시간과 성공 비율을 측정하였다. (Bw+ Tree의 경우, 삽입 작업과 삭제 작업과 같은 기본 작업이 원자적 연산으로 되어있다. 따라서, 실패한 연산수를 통하여 성공 비율을 측정하였다.)

#### Key Observations
Each leaf node in our 1,024x1,024-element bw-tree contained 64 elements. The operations involved traversing the tree structure and appending delta information to the leaf node if the number of deltas exceeded 8. We observed a positive correlation between time consumption and success ratio when the number of available keys ranged from 2 to 64. This suggests that as the congestion degree of a node increases, the overhead for modifications also increases linearly. However, when the number of available keys ranges from 64 to 1,024x1,024, the success ratio remains similar, and performance improves as the congestion degree decreases.

## New Version Design
#### Concept
The new design is akin to adding new roads to alleviate traffic congestion. By splitting a congested leaf node, we can create new paths to the same key range, improving overall response times. This design assumes that users can predict future workloads' congestion levels and choose to activate the splitting option for better performance.

#### Implementation
A boolean member, congestion_control, has been added to the class tree. Users can activate the new policy by setting tree->congestion_control to true.

#### Design Rational and Corretness
The new splitting policy requires criteria for identifying congestion levels. We have introduced new tables (success_count, op_count, op_base, and node_flag) alongside the existing mapping_table. These tables count operation attempts and successes for each leaf node, providing data to assess congestion levels. The decision to split or not is based on a success ratio threshold of 90%. Additionally, we use node_flag as an indicator to prevent merging of certain nodes.

### custom test cases
I developed specific test cases in 'bwtree_test_density'.
- BwtreeTest_db_init: Measures time to create a bw-tree structure with 1M keys.
- BwtreeTest_density_with_exist_db: Measures modification time within a given key range.
- BwtreeTest_density_with_exist_db_with_split_logic: Similar to the above but includes the split logic.

## Performance analysis
[Table2]는 이전 버전과 새 버전 간의 성능 차이를 보여준다. 특히 이전에 가장 낮은 성능을 보였던 연속된 16개 키에 대한 워크로드에서, 새 버전은 약 33%의 성능 향상을 달성하였다.
![image](https://user-images.githubusercontent.com/96645965/216049921-7d82db04-03f3-40b3-8ca7-34f1c4d63e6c.png)
[Table2]   
