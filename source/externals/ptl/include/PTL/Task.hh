#include "CommonHeader.h"

//
// MIT License
// Copyright (c) 2020 Jonathan R. Madsen
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software. THE SOFTWARE IS PROVIDED
// "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT
// LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
// PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
// HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
// ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
// WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
//
//
// ---------------------------------------------------------------
// Tasking class header file
//
// Class Description:
//
// This file defines the task types for TaskManager and ThreadPool
//
// ---------------------------------------------------------------
// Author: Jonathan Madsen (Feb 13th 2018)
// ---------------------------------------------------------------

#pragma once

#include "Globals.hh"
#include "VTask.hh"

#include <cstdint>
#include <functional>
#include <stdexcept>

namespace PTL
{
class ThreadPool;

//======================================================================================//

/// \brief The task class is supplied to thread_pool.
template <typename RetT>
class TaskFuture : public VTask
{
public:
    typedef std::promise<RetT> promise_type;
    typedef std::future<RetT>  future_type;
    typedef RetT               result_type;

public:
    // pass a free function pointer
    template <typename... Args>
    TaskFuture(Args&&... args)
    : VTask{ std::forward<Args>(args)... }
    {}

    virtual ~TaskFuture() = default;

    TaskFuture(const TaskFuture&) = delete;
    TaskFuture& operator=(const TaskFuture&) = delete;

    TaskFuture(TaskFuture&&) = default;
    TaskFuture& operator=(TaskFuture&&) = default;

public:
    // execution operator
    virtual future_type get_future() = 0;
    virtual void        wait()       = 0;
    virtual RetT        get()        = 0;
};

//======================================================================================//

/// \brief The task class is supplied to thread_pool.
template <typename RetT, typename... Args>
class PackagedTask : public TaskFuture<RetT>
{
public:
    typedef PackagedTask<RetT, Args...>       this_type;
    typedef std::promise<RetT>                promise_type;
    typedef std::future<RetT>                 future_type;
    typedef std::packaged_task<RetT(Args...)> packaged_task_type;
    typedef RetT                              result_type;
    typedef std::tuple<Args...>               tuple_type;

public:
    // pass a free function pointer
    template <typename FuncT>
    PackagedTask(FuncT func, Args... args)
    : TaskFuture<RetT>{ true, 0 }
    , m_ptask{ std::move(func) }
    , m_args{ args... }
    {}

    template <typename FuncT>
    PackagedTask(bool _is_native, intmax_t _depth, FuncT func, Args... args)
    : TaskFuture<RetT>{ _is_native, _depth }
    , m_ptask{ std::move(func) }
    , m_args{ args... }
    {}

    virtual ~PackagedTask() = default;

    PackagedTask(const PackagedTask&) = delete;
    PackagedTask& operator=(const PackagedTask&) = delete;

    PackagedTask(PackagedTask&&) = default;
    PackagedTask& operator=(PackagedTask&&) = default;

public:
    // execution operator
    virtual void operator()() final { mpl::apply(std::move(m_ptask), std::move(m_args)); }
    virtual future_type get_future() final { return m_ptask.get_future(); }
    virtual void        wait() final { return m_ptask.get_future().wait(); }
    virtual RetT        get() final { return m_ptask.get_future().get(); }

private:
    packaged_task_type m_ptask;
    tuple_type         m_args;
};

//======================================================================================//

/// \brief The task class is supplied to thread_pool.
template <typename RetT, typename... Args>
class Task : public TaskFuture<RetT>
{
public:
    typedef Task<RetT, Args...>               this_type;
    typedef std::promise<RetT>                promise_type;
    typedef std::future<RetT>                 future_type;
    typedef std::packaged_task<RetT(Args...)> packaged_task_type;
    typedef RetT                              result_type;
    typedef std::tuple<Args...>               tuple_type;

public:
    template <typename FuncT>
    Task(FuncT func, Args... args)
    : TaskFuture<RetT>{}
    , m_ptask{ std::move(func) }
    , m_args{ args... }
    {}

    template <typename FuncT>
    Task(bool _is_native, intmax_t _depth, FuncT func, Args... args)
    : TaskFuture<RetT>{ _is_native, _depth }
    , m_ptask{ std::move(func) }
    , m_args{ args... }
    {}

    virtual ~Task() = default;

    Task(const Task&) = delete;
    Task& operator=(const Task&) = delete;

    Task(Task&&)  = default;
    Task& operator=(Task&&) = default;

public:
    // execution operator
    virtual void operator()() final
    {
        if(m_ptask.valid())
            mpl::apply(std::move(m_ptask), std::move(m_args));
    }
    virtual future_type get_future() final { return m_ptask.get_future(); }
    virtual void        wait() final { return m_ptask.get_future().wait(); }
    virtual RetT        get() final { return m_ptask.get_future().get(); }

private:
    packaged_task_type m_ptask{};
    tuple_type         m_args{};
};

//======================================================================================//

/// \brief The task class is supplied to thread_pool.
template <typename RetT>
class Task<RetT, void> : public TaskFuture<RetT>
{
public:
    typedef Task<RetT>                 this_type;
    typedef std::promise<RetT>         promise_type;
    typedef std::future<RetT>          future_type;
    typedef std::packaged_task<RetT()> packaged_task_type;
    typedef RetT                       result_type;

public:
    template <typename FuncT>
    Task(FuncT func)
    : TaskFuture<RetT>()
    , m_ptask{ std::move(func) }
    {}

    template <typename FuncT>
    Task(bool _is_native, intmax_t _depth, FuncT func)
    : TaskFuture<RetT>{ _is_native, _depth }
    , m_ptask{ std::move(func) }
    {}

    virtual ~Task() = default;

    Task(const Task&) = delete;
    Task& operator=(const Task&) = delete;

    Task(Task&&)  = default;
    Task& operator=(Task&&) = default;

public:
    // execution operator
    virtual void        operator()() final { m_ptask(); }
    virtual future_type get_future() final { return m_ptask.get_future(); }
    virtual void        wait() final { return m_ptask.get_future().wait(); }
    virtual RetT        get() final { return m_ptask.get_future().get(); }

private:
    packaged_task_type m_ptask{};
};

//======================================================================================//

/// \brief The task class is supplied to thread_pool.
template <>
class Task<void, void> : public TaskFuture<void>
{
public:
    typedef void                       RetT;
    typedef Task<void, void>           this_type;
    typedef std::promise<RetT>         promise_type;
    typedef std::future<RetT>          future_type;
    typedef std::packaged_task<RetT()> packaged_task_type;
    typedef RetT                       result_type;

public:
    template <typename FuncT>
    explicit Task(FuncT func)
    : TaskFuture<RetT>{}
    , m_ptask{ std::move(func) }
    {}

    template <typename FuncT>
    Task(bool _is_native, intmax_t _depth, FuncT func)
    : TaskFuture<RetT>{ _is_native, _depth }
    , m_ptask{ std::move(func) }
    {}

    virtual ~Task() = default;

    Task(const Task&) = delete;
    Task& operator=(const Task&) = delete;

    Task(Task&&)  = default;
    Task& operator=(Task&&) = default;

public:
    // execution operator
    virtual void        operator()() final { m_ptask(); }
    virtual future_type get_future() final { return m_ptask.get_future(); }
    virtual void        wait() final { return m_ptask.get_future().wait(); }
    virtual RetT        get() final { return m_ptask.get_future().get(); }

private:
    packaged_task_type m_ptask{};
};

//======================================================================================//

}  // namespace PTL
