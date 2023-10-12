**Data Distribution**
  Data Partitioning: Split the input data into chunks.
    what:
      graph data:
        (explain)
    why:
      splitting the graph data allows the multiple threads to pull data and work on it independently. we do need to ensure that the data is kept track of and not worked on multiple times
    where:
      This can be done either before Peregrine preprocessor or after but before the actual work is done.
    how
  Data Storage: Use distributed file systems like Hadoop's HDFS or cloud storage solutions to store partitioned data, ensuring data availability to all nodes.
