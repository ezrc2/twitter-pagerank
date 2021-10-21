# Higgs Boson Twitter Pagerank

**Location of code:**

`include/` and `src/` folders

**Location of data:**

`data/`

**Location of results**:
```
diagram.png (force directed graph)
data/matrix_data.txt (DFS results)
data/ranked_users.txt (PageRank results)
```

## Commands

#### To compile:
```
make
```
The executable created is called `project`.

#### DFS
```
./project dfs data/higgs-activity_time.txt data/matrix_data.txt data/DFS_out.txt
```

The general form is:

```
./project dfs [input file path] [matrix output file path] [dfs output file path]
```

Estimated runtime: ~30 minutes on EWS machine

#### PageRank
```
./project pagerank data/higgs-activity_time.txt data/adjacency_matrix.txt data/ranked_users.txt
```
The general form is:
```
./project pagerank [input file path] [matrix output file path] [output file path]
```

Estimated runtime: ~2 minutes on EWS machine

#### Force-Directed Graph
```
./project diagram data/ranked_users.txt data/matrix_data.txt diagram.png
```
The general form is:
```
./project diagram [pagerank data file path] [matrix data input path] [output_image.png]
```

Estimated runtime: ~2 minutes on EWS machine

## Tests

#### To compile and run the test cases
```
make test
./test
```

#### Test Suite Description:

In order to test the algorithms we made a sample dataset in our tests folder called `sample_data.txt`. In our `tests.cpp` file we test matrix constructing, DFS, and PageRank by utilizing the dataset and requiring that they match up with the expected results. For our force-directed algorithm test we check to see that it outputs a file with the data inputted from the test as that'd allow us to know it's able to successfully input the data and make a force-directed graph.
