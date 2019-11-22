# [project 3](https://maryash.github.io/135/projects/project_03.html)

```
./mission rows cols num debris mpr
./mission 25 30 10  0.5  0.0001  12345 
./mission 25 30 10  0.5
```

```
./test.rb ./mission
time ./test.rb ./mission
```

### Original 
```
Average collection rate:
	all	   189 	 -> 	(Score 16.1)
mpr:
	0.0	   190
	0.0002	   218
	0.005	   193
	0.02	   184
	0.4	   159
debris:
	0.2	     0
	0.5	     0
	0.8	  1105
num:
	2	   131
	5	   138
	15	   186
	30	   302
rows:
	15	   233
	35	   145
cols:
	15	   233
	35	   145
```

### 11/21/19 13:00 Kernel
```
Average collection rate:
	all	   345 	 -> 	(Score 29.4)
mpr:
	0.0	   469 
	0.0002	   526 
	0.005	   323 
	0.02	   243 
	0.4	   165 
debris:
	0.2	     0 
	0.5	   135 
	0.8	  1185 
num:
	2	   295 
	5	   330 
	15	   348 
	30	   408 
rows:
	15	   426 
	35	   264 
cols:
	15	   439 
	35	   251 
```

### 11/21/19 16:20 Repair bots 
```
Average collection rate:
	all	   427 	 -> 	(Score 36.3)
mpr:
	0.0	   516 
	0.0002	   493 
	0.005	   445 
	0.02	   470 
	0.4	   212 
debris:
	0.2	     0 
	0.5	   288 
	0.8	  1244 
num:
	2	   367 
	5	   399 
	15	   417 
	30	   526 
rows:
	15	   505 
	35	   350 
cols:
	15	   528 
	35	   326 
```

### 11/21/19 16:20 Further neighbors
```
Average collection rate:
	all	   468 	 -> 	(Score 39.8)
mpr:
	0.0	   550 
	0.0002	   627 
	0.005	   472 
	0.02	   481 
	0.4	   209 
debris:
	0.2	     0 
	0.5	   357 
	0.8	  1266 
num:
	2	   462 
	5	   421 
	15	   468 
	30	   519 
rows:
	15	   541 
	35	   394 
cols:
	15	   570 
	35	   365 
```

## 11/21/19 19:00 ~Least "treaded" debris field~ Further neighbors
```
Average collection rate:
	all	   500 	 -> 	(Score 42.6)
mpr:
	0.0	   653 
	0.0002	   569 
	0.005	   572 
	0.02	   470 
	0.4	   238 
debris:
	0.2	     0 
	0.5	   369 
	0.8	  1280 
num:
	2	   416 
	5	   532 
	15	   523 
	30	   530 
rows:
	15	   598 
	35	   403 
cols:
	15	   627 
	35	   373 
```


## 11/21/19 19:20 Least "treaded" debris field
```
Average collection rate:
	all	   528 	 -> 	(Score 44.9)
mpr:
	0.0	   594 
	0.0002	   636 
	0.005	   663 
	0.02	   546 
	0.4	   200 
debris:
	0.2	     0 
	0.5	   433 
	0.8	  1276 
num:
	2	   564 
	5	   530 
	15	   494 
	30	   522 
rows:
	15	   666 
	35	   389 
cols:
	15	   611 
	35	   444 
```

## 11/22/19 2:40 Bounding
```
Average collection rate:
	all	   621 	 -> 	(Score 52.8)
mpr:
	0.0	   754 
	0.0002	   741 
	0.005	   746 
	0.02	   610 
	0.4	   254 
debris:
	0.2	     0 
	0.5	   536 
	0.8	  1353 
num:
	2	   626 
	5	   693 
	15	   570 
	30	   595 
rows:
	15	   700 
	35	   542 
cols:
	15	   728 
	35	   514 
```

## Do Not Repeat
- avoid previous location
- bounding from all sides... kinda weird but I'll take it
