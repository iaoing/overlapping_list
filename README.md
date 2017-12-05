## overlapping list  

- Spliting nodes when overlapping and guaranteeing infomations not lost.
- When query one or a range of numbers, return all the targets.
- Not support delete operation (This operation will be involve garbage collect and nodes merge, maybe supported in the future).

#### no overlapping

1. TYPE-1: new range in the left
   - \[10, 20] + \[ 5,  9]  ---->> \[ 5,  9]; \[10, 20]
2. TYPE-2: new range in the right
   - \[10, 20] + \[21, 22]  ---->> \[10, 20]; \[21, 22]

#### overlapping type
1. TYPE-1: left overlapping
   - \[10, 20] + \[ 5, 15]  ---->> \[ 5,  9]; \[10, 15]; \[16, 20]
2. TYPE-2: right overlapping
   - \[10, 20] + \[15, 25]  ---->> \[10, 14]; \[15, 20]; \[21, 25]
3. TYPE-3: new range contained by prevs
   - \[10, 20] + \[13, 19]  ---->> \[10, 12]; \[13, 19]; \[20, 20]
4. TYPE-4: new range contains prevs
   - \[10, 20] + \[ 5, 25]  ---->> \[ 5,  9]; \[10, 20]; \[21, 25]

#### NOTE: Some boundary case should be attentive.
