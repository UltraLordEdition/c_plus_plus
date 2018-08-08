#include "stdafx.h"
#include <iostream>
#include <tuple>
#include <utility>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

// Перечислимый тип для статуса задач
enum class TaskStatus
{
    NEW,            // новая
    IN_PROGRESS,    // в разработке
    TESTING,        // на тестировании
    DONE            // завершена
};

// Объявляем тип-синоним для map<TaskStatus, int>,
// позволяющего хранить количество задач каждого статуса
using TasksInfo = map<TaskStatus, int>;

class TeamTasks
{
public:
    // Получить статистику по статусам задач конкретного разработчик
    const TasksInfo& GetPersonTasksInfo(const string& person) const
    {
        return db.at(person);
    }

    // Добавить новую задачу (в статусе NEW) для конкретного разработчитка
    void AddNewTask(const string& person)
    {
        db[person][TaskStatus::NEW]++;
        db[person][TaskStatus::IN_PROGRESS];
        db[person][TaskStatus::TESTING];
        db[person][TaskStatus::DONE];
    }

    
    // Обновить статусы по данному количеству задач конкретного разработчика,
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

// Принимаем словарь по значению, чтобы иметь возможность
// обращаться к отсутствующим ключам с помощью [] и получать 0,
// не меняя при этом исходный словарь
void PrintTasksInfo(TasksInfo tasks_info) {
    cout << tasks_info[TaskStatus::NEW] << " new tasks" <<
        ", " << tasks_info[TaskStatus::IN_PROGRESS] << " tasks in progress" <<
        ", " << tasks_info[TaskStatus::TESTING] << " tasks are being tested" <<
        ", " << tasks_info[TaskStatus::DONE] << " tasks are done" << endl;
}

int main() {         
    /***************************************************************************************************************
                                                            TESTING
    
    TasksInfo updated_tasks, untouched_tasks, current_tasks, sum_tasks;
    int task_count = 4;                                        //2       |2       |3       |    //8       |
                                                               //Y       |        |        |    //        |
    current_tasks[TaskStatus::NEW] = 3;                        //3 = 0-1 |1 = 0-0 |0 = 0-0 |0   //2 = 0-0 | 0
    current_tasks[TaskStatus::IN_PROGRESS] = 2;                //0 = 2-0 |2 = 1-1 |2 = 0-0 |0   //5 = 2-0 | 2
    current_tasks[TaskStatus::TESTING] = 4;                    //0 = 0-0 |0 = 1-0 |1 = 2-0 |2   //6 = 5-5 | 10
    current_tasks[TaskStatus::DONE] = 1;                       //0 = 0-0 |0 = 0-0 |0 = 1-0 |1   //7 = 1-7 | 8
  
    updated_tasks = getUpTask(current_tasks, task_count);
    untouched_tasks = getUnTask(current_tasks, task_count);
    //sum_tasks = updated_tasks + untouched_tasks;

    PrintTasksInfo(updated_tasks);
    PrintTasksInfo(untouched_tasks);
    ****************************************************************************************************************/
    /*
    
    TeamTasks tasks;
    TasksInfo updated_tasks, untouched_tasks;
    
    for (int i = 0; i < 5; ++i) {
        tasks.AddNewTask("Alice");
    }
     
    tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Alice", 5);
    PrintTasksInfo(updated_tasks);
    PrintTasksInfo(untouched_tasks);

    tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Alice", 5);
    PrintTasksInfo(updated_tasks);
    PrintTasksInfo(untouched_tasks);
       
    tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Alice", 1);
    PrintTasksInfo(updated_tasks);
    PrintTasksInfo(untouched_tasks);
    
    for (int i = 0; i < 5; ++i) {
        tasks.AddNewTask("Alice");
    }
  
    cout << " ";
    PrintTasksInfo(tasks.GetPersonTasksInfo("Alice"));

    tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Alice", 2);
    PrintTasksInfo(updated_tasks);
    PrintTasksInfo(untouched_tasks);
    
    cout << " ";
    PrintTasksInfo(tasks.GetPersonTasksInfo("Alice"));

    tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Alice", 4);
    PrintTasksInfo(updated_tasks);
    PrintTasksInfo(untouched_tasks);

    cout << " ";
    PrintTasksInfo(tasks.GetPersonTasksInfo("Alice"));
    
    /*
    TeamTasks tasks;
    tasks.AddNewTask("Ilia");
    for (int i = 0; i < 3; ++i) {
        tasks.AddNewTask("Ivan");
    }
    cout << "Ilia's tasks: ";
    PrintTasksInfo(tasks.GetPersonTasksInfo("Ilia"));
    cout << "Ivan's tasks: ";
    PrintTasksInfo(tasks.GetPersonTasksInfo("Ivan"));

    TasksInfo updated_tasks, untouched_tasks;

    tie(updated_tasks, untouched_tasks) =
        tasks.PerformPersonTasks("Ivan", 2);
    cout << "Updated Ivan's tasks: ";
    PrintTasksInfo(updated_tasks);
    cout << "Untouched Ivan's tasks: ";
    PrintTasksInfo(untouched_tasks);

    tie(updated_tasks, untouched_tasks) =
        tasks.PerformPersonTasks("Ivan", 2);
    cout << "Updated Ivan's tasks: ";
    PrintTasksInfo(updated_tasks);
    cout << "Untouched Ivan's tasks: ";
    PrintTasksInfo(untouched_tasks);
            */
    TeamTasks tasks;

    tasks.AddNewTask("test");
    tasks.AddNewTask("test");

    tasks.PerformPersonTasks("test", 1);

    PrintTasksInfo(tasks.GetPersonTasksInfo("test"));

    tasks.PerformPersonTasks("test", 3);

    PrintTasksInfo(tasks.GetPersonTasksInfo("test"));
    tasks.AddNewTask("test");
    tasks.PerformPersonTasks("test", 3);
    PrintTasksInfo(tasks.GetPersonTasksInfo("test"));

   return 0;
}