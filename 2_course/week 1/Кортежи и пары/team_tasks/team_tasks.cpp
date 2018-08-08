#include <tuple>
#include <map>
#include <vector>
#include <algorithm>

class TeamTasks
{
public:
    // ѕолучить статистику по статусам задач конкретного разработчик
    const TasksInfo& GetPersonTasksInfo(const string& person) const
    {
        return db.at(person);
    }

    // ƒобавить новую задачу (в статусе NEW) дл€ конкретного разработчитка
    void AddNewTask(const string& person)
    {
        db[person][TaskStatus::NEW]++;
        db[person][TaskStatus::IN_PROGRESS];
        db[person][TaskStatus::TESTING];
        db[person][TaskStatus::DONE];
    }


    // ќбновить статусы по данному количеству задач конкретного разработчика,
    // подробности см. ниже
   tuple<TasksInfo, TasksInfo> PerformPersonTasks(const string& person, int task_count)
    {
        TasksInfo updated_tasks, untouched_tasks, current_tasks;

        int carry, residue, next_status;

        current_tasks = db[person];
        int summ = current_tasks[TaskStatus::NEW] +
                   current_tasks[TaskStatus::IN_PROGRESS] +
                   current_tasks[TaskStatus::TESTING];

        if (task_count > summ && task_count > 0)
        {
            task_count = summ;
        }

        for (auto item : current_tasks)
        {
            carry = getToPush(current_tasks[item.first], task_count);
            if (carry > 0 && item.first != TaskStatus::DONE)
            {
                next_status = static_cast<int>(item.first) + 1;
                updated_tasks[static_cast<TaskStatus>(next_status)] = carry;
            }
            if ((current_tasks[item.first] - carry) > 0)
            {
                untouched_tasks[item.first] = current_tasks[item.first] - carry;
            }
        }
        db[person] = getResultTask(updated_tasks, untouched_tasks);
        untouched_tasks.erase(TaskStatus::DONE);
        return {updated_tasks,untouched_tasks};
     }

private:
   map<string, TasksInfo> db;

   int getToPush(int status, int& task_count)
   {
       int Min = min(status, task_count);
       task_count = task_count - status;
       if (task_count < 0)
       {
           task_count = 0;
       }
       return Min;
   }

   TasksInfo getResultTask(TasksInfo updated_tasks, TasksInfo untouched_tasks)
   {
       TasksInfo result_tasks,sum;
       result_tasks[TaskStatus::NEW] = 0;
       result_tasks[TaskStatus::IN_PROGRESS] = 0;
       result_tasks[TaskStatus::TESTING] = 0;
       result_tasks[TaskStatus::DONE] = 0;
       for (auto item : result_tasks)
       {
           result_tasks[item.first] = updated_tasks[item.first] + untouched_tasks[item.first];
           if (result_tasks[item.first] > 0)
           {
               sum[item.first] = result_tasks[item.first];
           }
       }
       return sum;
   }
};