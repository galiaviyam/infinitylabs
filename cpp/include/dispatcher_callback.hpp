/****************************************/
/*                                      */   
/*   Developer: Gali Aviyam             */
/*   Project:   Dispatcher - Callback   */
/*   Date:      09/06/23                */
/*   Reviewer:  Itay                    */
/*                                      */
/****************************************/

#ifndef ILRD_RD136_7_DISPATCHER_CALLBACK_HPP
#define ILRD_RD136_7_DISPATCHER_CALLBACK_HPP

#include <list>             // list
#include <iterator>         // iterator

namespace ilrd
{

// EVENT must be copyable

template <class EVENT>
class Dispatcher;

template <class EVENT>
class CallbackBase
{
public:
    CallbackBase() = default;
    virtual ~CallbackBase() = default;
    CallbackBase(const CallbackBase&) = delete;
    CallbackBase& operator=(const CallbackBase&) = delete;
    
    virtual void Notify(EVENT event) =0;
    virtual void Close() =0;
    void Unregister();

private:
    void SetDispatcher(Dispatcher<EVENT> *dispatcher);
    friend Dispatcher<EVENT>;

    Dispatcher<EVENT> *m_dispatcher = 0;
};

template <class OBS, class EVENT>
class Callback : public CallbackBase<EVENT>
{
    typedef void (OBS::*NotifyFunc_t)(EVENT event);
    typedef void (OBS::*CloseFunc_t)();

public:
    Callback(OBS *observer, NotifyFunc_t notify, CloseFunc_t close);
    ~Callback();
    void Notify(EVENT event);
    void Close();

private:
    OBS *m_observer;
    NotifyFunc_t m_notify;
    CloseFunc_t m_close;
};

template <class EVENT>
class Dispatcher
{
public:
    Dispatcher() = default;
    ~Dispatcher() = default;
    Dispatcher(const Dispatcher&) = delete;
    Dispatcher& operator=(const Dispatcher&) = delete;

    void Register(CallbackBase<EVENT> *callback);
    void Unregister(CallbackBase<EVENT> *callback);
    void NotifyAll(EVENT event);
    void CloseAll();

private:
    typedef CallbackBase<EVENT>* subscriber_t;

    std::list<subscriber_t> m_subscribers;
};

/*------------------------------- CallbackBase -------------------------------*/
template <class EVENT>
void CallbackBase<EVENT>::Unregister()
{
    if (nullptr != m_dispatcher)
    {
        m_dispatcher->Unregister(this);
    }
}

template <class EVENT>
void CallbackBase<EVENT>::SetDispatcher(Dispatcher<EVENT> *dispatcher)
{
    m_dispatcher = dispatcher;
}

/*--------------------------------- Callback ---------------------------------*/
template <class OBS, class EVENT>
Callback<OBS, EVENT>::Callback(OBS *observer,
    NotifyFunc_t notify, CloseFunc_t close): m_observer(observer),
    m_notify(notify), m_close(close) {}

template <class OBS, class EVENT>
Callback<OBS, EVENT>::~Callback()
{
    CallbackBase<EVENT>::Unregister();
}

template <class OBS, class EVENT>
void Callback<OBS, EVENT>::Notify(EVENT event)
{
    (m_observer->*m_notify)(event);
}

template <class OBS, class EVENT>
void Callback<OBS, EVENT>::Close()
{
    (m_observer->*m_close)();
}

/*-------------------------------- Dispatcher --------------------------------*/
template <class EVENT>
void Dispatcher<EVENT>::Register(CallbackBase<EVENT> *callback)
{
    m_subscribers.push_back(callback);
    callback->SetDispatcher(this);
}

template <class EVENT>
void Dispatcher<EVENT>::Unregister(CallbackBase<EVENT> *callback)
{
    m_subscribers.remove(callback);
    callback->SetDispatcher(0);
}

template <class EVENT>
void Dispatcher<EVENT>::NotifyAll(EVENT event)
{
    auto copy = m_subscribers;
    for (auto &iter : copy)
    {
        iter->Notify(event);
    }
}

template <class EVENT>
void Dispatcher<EVENT>::CloseAll()
{
    auto copy = m_subscribers;

    for (auto &iter : copy)
    {
        iter->Close();
    }
}

}

#endif /* ILRD_RD136_7_DISPATCHER_CALLBACK_HPP */