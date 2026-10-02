
// patterns

1. exactly K = atMost(K) - atMost(K-1)
2. subarray sum = prefix difference
3. subarray XOR = prefix XOR
4. divisible by K = equal prefix remainders
5. gcd(a,b) = gcd(a-b,b)
6. x & (x-1) removes lowest set bit
7. x & -x isolates lowest set bit
8. x is power of 2 <=> x&(x-1)==0
9. sorted + pair condition -> two pointers
10. monotonic feasibility -> binary search answer
11. next greater/smaller -> monotonic stack
12. window min/max -> monotonic deque
13. unweighted shortest path -> BFS
14. 0/1 weighted -> 0-1 BFS
15. non-negative weighted -> Dijkstra
16. dependency/order -> topological sort
17. connectivity + merge -> DSU
18. tree path distance -> depth + LCA
19. subtree -> Euler interval
20. static RMQ -> Sparse Table
21. range update + query -> Lazy Segment Tree
22. n <= 20 -> bitmask
23. n <= 40 -> meet in the middle
24. exactly one simple path -> tree
25. bipartite <=> no odd cycle
26. DAG -> topo + DP
27. sum of degrees = 2E
28. odd-degree vertices occur in pairs
29. number of subarrays = n(n+1)/2
30. tree with n nodes has n-1 edges
31. dense graph -> consider complement graph
32. difficult forward process -> reverse it
33. count instead of construct
34. total - bad = good
35. identify the invariant before coding
36. prefix/suffix preprocessing -> avoid repeated range computation
37. range add + point query -> Difference Array
38. range sum -> Prefix Sum
39. many point updates + prefix/range sums -> Fenwick Tree
40. many range queries + no updates -> Sparse Table
41. many range updates + range queries -> Lazy Segment Tree
42. coordinate values huge but relative order matters -> Coordinate Compression
43. duplicate/occurrence questions -> Frequency Map / Counting
44. array sorted + optimize pair/triple -> Two Pointers
45. sorted + nearest/first valid -> Binary Search / lower_bound
46. choose minimum/maximum locally with provable exchange -> Greedy
47. maximize/minimize contribution independently -> Contribution Technique
48. answer depends only on parity -> reduce modulo 2
49. answer depends on value modulo K -> work with remainders
50. prefix property repeats -> detect cycle / use first occurrence
51. state repeats -> DP / memoization
52. same state from multiple paths -> shortest/optimal state DP
53. negative effect disappears after sorting -> sort first
54. intervals overlap -> sort by left/right endpoint
55. interval scheduling -> sort by finishing time
56. range of active intervals -> sweep line
57. events at endpoints -> sweep line + event ordering
58. need nearest previous greater/smaller -> Monotonic Stack
59. need nearest maximum/minimum in window -> Monotonic Deque
60. each element pushed/popped once -> O(n) amortized
61. constraints n <= 20 -> bitmask / subset enumeration
62. constraints n <= 25 -> meet in the middle often possible
63. constraints n <= 40 -> meet in the middle
64. constraints n <= 60 -> bit tricks / meet in the middle / greedy depending on structure
65. graph with one path between every pair -> Tree
66. connected graph with n-1 edges -> Tree
67. tree + remove one edge -> exactly two components
68. tree + add one edge -> exactly one cycle
69. tree distance(u,v) = depth[u] + depth[v] - 2*depth[lca(u,v)]
70. subtree query -> Euler flattening
71. path query on tree -> HLD / Binary Lifting depending on operation
72. tree DP -> answer from children to parent
73. rerooting -> calculate answer for one root, then transfer to neighbours
74. graph with no cycles -> DAG / Tree depending on connectivity
75. DAG shortest/longest path -> Topological DP
76. DAG DP -> every edge processed once after topological ordering
77. unweighted graph shortest path -> BFS
78. edges with weights 0/1 -> 0-1 BFS
79. non-negative weights -> Dijkstra
80. negative edges -> Bellman-Ford / DAG DP if DAG
81. all-pairs shortest path, small n -> Floyd-Warshall
82. minimum spanning tree -> Kruskal / Prim
83. dynamic connectivity with only additions -> DSU
84. connectivity offline with deletions -> reverse process + DSU
85. directed graph dependencies -> Topological Sort
86. directed cycle -> DFS colors / Kahn
87. strongly connected behaviour -> SCC
88. bipartite graph -> 2-coloring
89. bipartite <=> no odd cycle
90. complement graph can be much sparser -> traverse complement instead
91. graph answer depends on degree -> sum/degree counting
92. sum of degrees = 2E
93. number of odd-degree vertices is even
94. connected tree edges = vertices - 1
95. complete graph edges = n(n-1)/2
96. complete bipartite graph edges = n*m
97. count pairs -> think unordered pair = n(n-1)/2
98. count subarrays -> n(n+1)/2
99. count subarrays with property -> prefix state + frequency map
100. prefix sum equal at i,j -> subarray sum between them is 0
101. prefix remainder equal -> subarray sum divisible by K
102. prefix XOR equal -> subarray XOR is 0
103. subarray XOR = X -> previous prefix XOR = current XOR ^ X
104. exactly K -> atMost(K) - atMost(K-1)
105. exactly target sum with positive values -> sliding window
106. negative values present -> sliding window usually fails; consider prefix sum/map
107. maximize minimum / minimize maximum -> Binary Search on Answer
108. feasibility changes false -> true monotonically -> Binary Search
109. can construct answer from optimal value -> binary search + reconstruction
110. total - bad = good
111. complement of condition may be easier to count
112. count instead of construct
113. construct from counts/frequencies when order is irrelevant
114. identical elements can often be grouped by frequency
115. permutation symmetry -> sort / canonicalize states
116. state only depends on last few elements -> small-state DP
117. future depends only on current state, not history -> DP state compression
118. transitions form a small graph -> shortest path on states
119. operation applied repeatedly with same transition -> Matrix Exponentiation
120. repeated squaring / doubling -> O(log n)
121. huge n but small states -> DP transition matrix
122. huge coordinate range but few used coordinates -> Coordinate Compression
123. values only matter by relative order -> rank/compress
124. many queries on static data -> preprocess
125. many identical queries -> memoize/cache
126. process queries offline -> sort queries/events to reduce complexity
127. modifications undoable -> rollback / reverse processing
128. each element participates in O(log n) structures -> often O(n log n)
129. nested loops are not automatically O(n^2) -> check total pointer movement
130. two pointers/monotonic stack/deque -> prove each element moves/pushes/pops O(1) times
131. constraints dominate algorithm choice -> derive target complexity before coding
132. when stuck -> look for invariant, monotonicity, symmetry, or state compression
133. maximum subarray sum -> Kadane
136. inversion counting -> Fenwick / Merge Sort
138. enumerate submasks -> (sub-1)&mask
139. masks + submasks -> O(3^n)
140. subset-dependent state -> Bitmask DP
142. digit constraints on numbers <= N -> Digit DP
143. repeated graph state -> Functional Graph / cycle
149. subarray gcd -> only O(log A) distinct gcds per endpoint
150. invariant -> track the quantity that never changes
156. ancestor jumping / repeated doubling -> Binary Lifting
160. first position satisfying condition -> Segment Tree / binary search
163. at least/at most -> complement / inclusion-exclusion
168. nested + non-crossing -> Catalan
176. graph node + extra parameter -> expanded-state BFS/Dijkstra
183. kth smallest/largest -> Binary Search on Value