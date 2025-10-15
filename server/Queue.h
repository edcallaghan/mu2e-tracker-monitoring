// Ed Callaghan
// Concrete choice of queue object
// August 2025

#ifndef QUEUE_H
#define QUEUE_H

#include <memory>
#include "PriorityQueue.h"
#include "Task.h"

using Queue = PriorityQueue< std::shared_ptr<Task> >;

#endif
