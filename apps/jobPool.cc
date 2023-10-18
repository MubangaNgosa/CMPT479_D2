class jobPool {
    Queue<Task> tasks;
    
    void addTask(Task task) {
        // tasks.enqueue(task);
    }

    Task getTask() {
        if (!task.isEmpty()) {
            return tasks.dequeue();
        }
        // return tasks.dequeue();
    }
}