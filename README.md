## overlapping list  

- Spliting nodes when overlapping and guaranteeing infomations not lost.
- When query one or a range of numbers, return all the targets.
- Not support delete operation (This operation will be involve garbage collect and nodes merge, maybe supported in the future).

#### no overlapping

1. TYPE-1: new range in the left
   - [10, 20) + [ 5, 10)  ---->> [ 5, 10); [10, 20)
2. TYPE-2: new range in the right
   - [10, 20) + [20, 22)  ---->> [10, 20); [20, 22)

#### overlapping type
1. TYPE-1: left overlapping
   - [10, 20) + [ 5, 15)  ---->> [ 5, 10); [10, 15); [15, 20)
2. TYPE-2: right overlapping
   - [10, 20) + [15, 25)  ---->> [10, 15); [15, 20); [20, 25)
3. TYPE-3: new range contained by prevs
   - [10, 20) + [13, 19)  ---->> [10, 13); [13, 19); [19, 20)
4. TYPE-4: new range contains prevs
   - [10, 20) + [ 5, 25)  ---->> [ 5, 10); [10, 20); [20, 25)
