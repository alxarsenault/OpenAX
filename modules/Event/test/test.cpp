//
//  main.cpp
//  axEventTest
//
//  Created by Alexandre Arsenault on 2015-05-12.
//  Copyright (c) 2015 Alexandre Arsenault. All rights reserved.
//

#include <iostream>
#include <string>
#include "axEvent.h"
#include "axEventManager.h"
#include "axTimer.h"
#include "axMsg.h"

class Obj1 : public ax::Event::Object
{
public :
    
    enum : ax::Event::Id { OBJ1_EVT_0 };

    class Msg : public ax::Event::Msg
    {
    public:
        Msg(const std::string& msg): _msg(msg) { }
        
        virtual ax::Event::Msg* GetCopy() { return new Msg(*this); };
        
        std::string GetMsg() const { return _msg; }
        
    private:
        std::string _msg;
    };
    
    Obj1(ax::Event::Manager* evt_manager):
    ax::Event::Object(evt_manager)
    {
        AddConnection(OBJ1_EVT_0, GetOnEventObj1_id_0());
    }
    
    axEVENT_ACCESSOR(Msg, OnEventObj1_id_0);
    
private:
    void OnEventObj1_id_0(const Msg& msg)
    {
        std::cout << "Obj1 event : " << msg.GetMsg() << std::endl;
    }
};

class Obj2 : public ax::Event::Object
{
public:
    enum : ax::Event::Id { OBJ2_EVT_0 };
    
    typedef ax::Event::SimpleMsg<double> Msg;
    
    Obj2(ax::Event::Manager* evt_manager):
    ax::Event::Object(evt_manager)
    {
        AddConnection(OBJ2_EVT_0, GetOnEventObj2_id_0());
    }
    
    axEVENT_ACCESSOR(Msg, OnEventObj2_id_0);
    
private:
    void OnEventObj2_id_0(const Msg& msg)
    {
        std::cout << "Obj2 event : " << msg.GetMsg() << std::endl;
    }
};

int main(int argc, const char * argv[])
{
    std::cout << "Program start." << std::endl;
    
    ax::Event::Manager evt_manager;
    
    //--------------------------------------------------------------------------
    // Event with class heritage.
    //--------------------------------------------------------------------------
    Obj1 obj1(&evt_manager);
    obj1.PushEvent(Obj1::OBJ1_EVT_0, new Obj1::Msg("Msg test 1"));
    obj1.PushEvent(Obj1::OBJ1_EVT_0, new Obj1::Msg("Msg test 2"));
    
    evt_manager.CallNext();
    evt_manager.CallNext();
    
    //--------------------------------------------------------------------------
    // Event with class heritage and SimpleMsg template.
    //--------------------------------------------------------------------------
    Obj2 obj2(&evt_manager);
    obj2.PushEvent(Obj2::OBJ2_EVT_0, new Obj2::Msg(9.26));
    obj2.PushEvent(Obj2::OBJ2_EVT_0, new Obj2::Msg(4.9826));
    
    evt_manager.CallNext();
    evt_manager.CallNext();
    
    //--------------------------------------------------------------------------
    // Event on the fly with lamda and ax::Event::StringMsg.
    //--------------------------------------------------------------------------
    ax::Event::Object obj3(&evt_manager);
    obj3.AddConnection(0, [](ax::Event::Msg* msg)
    {
        ax::Event::StringMsg* stringMsg = static_cast<ax::Event::StringMsg*>(msg);
        
        std::cout << "obj3 event : " << stringMsg->GetMsg() << std::endl;
    });
    
    obj3.PushEvent(0, new ax::Event::StringMsg("Simple str msg"));
    
    evt_manager.CallNext();
    
    //--------------------------------------------------------------------------
    // Event on the fly with lamda and ax::Event::SimpleMsg.
    //--------------------------------------------------------------------------
    ax::Event::Object obj4(&evt_manager);
    obj4.AddConnection(0, [](ax::Event::Msg* msg)
    {
        ax::Event::SimpleMsg<int>& s_msg = ax::Event::SimpleMsg<int>::Cast(msg);
        
        std::cout << "obj4 event : " << s_msg.GetMsg() << std::endl;
    });
    
    obj4.PushEvent(0, new ax::Event::SimpleMsg<int>(92));
    
    evt_manager.CallNext();
    
    
    //--------------------------------------------------------------------------
    // ax::Event::Timer event test.
    //--------------------------------------------------------------------------
    ax::Event::Function timer1_evt = [](ax::Event::Msg* msg)
    {
        std::cout << "timer1 event" << std::endl;
    };
    
    ax::Event::Timer timer1(&evt_manager, timer1_evt);
    timer1.StartTimer(ax::Event::Timer::TimeMs(200), ax::Event::Timer::TimeMs(1000));
    
    
    ax::Event::Function timer2_evt = [](ax::Event::Msg* msg)
    {
        ax::Event::Timer::Msg* timerMsg = static_cast<ax::Event::Timer::Msg*>(msg);
        
        double count = timerMsg->GetTime().count();
        std::cout << "timer2 event : " << count << std::endl;
    };
    ax::Event::Timer timer2(&evt_manager, timer2_evt);
    timer2.StartTimer(ax::Event::Timer::TimeMs(100),
                      ax::Event::Timer::TimeMs(1000));
    
    ax::Event::Timer::TimeMs length(2000);
    ax::Event::Timer::TimeMs time_count(0);
    ax::Event::Timer::TimeMs sleep_time(10);

    
    // Simulate a main loop program.
    while(time_count < length)
    {
        time_count += sleep_time;
        std::this_thread::sleep_for(sleep_time);
        evt_manager.CallNext();
    }
    
    //--------------------------------------------------------------------------
    // Call event that is not in the event map.
    //--------------------------------------------------------------------------
    ax::Event::Object obj5(&evt_manager);
    obj5.PushEvent(0, new ax::Event::SimpleMsg<int>(92));
    
    evt_manager.CallNext();
    
    //--------------------------------------------------------------------------
    // Call multiple event with the same connection.
    //--------------------------------------------------------------------------
    ax::Event::Object obj6(&evt_manager);
    
    obj6.AddConnection(0, [](ax::Event::Msg* msg)
    {
        ax::Event::SimpleMsg<int>& s_msg = ax::Event::SimpleMsg<int>::Cast(msg);
        std::cout << "obj6 event 1 : " << s_msg.GetMsg() << std::endl;
    });
    
    obj6.AddConnection(0, [](ax::Event::Msg* msg)
    {
        ax::Event::SimpleMsg<int>& s_msg = ax::Event::SimpleMsg<int>::Cast(msg);
        std::cout << "obj6 event 2 : " << s_msg.GetMsg() << std::endl;
    });
    
    
    obj6.PushEvent(0, new ax::Event::SimpleMsg<int>(6273));
    
    evt_manager.CallNext();
    evt_manager.CallNext();
    
    //--------------------------------------------------------------------------
    // Push object that is not connected.
    //--------------------------------------------------------------------------
    evt_manager.PushEvent(92783867, 0, new ax::Event::SimpleMsg<int>(9999));
    
    //--------------------------------------------------------------------------
    // Remove object connection.
    //--------------------------------------------------------------------------
    evt_manager.RemoveObjectConnection(obj1.GetId());
    obj1.PushEvent(0, new Obj1::Msg("Msg test 2"));
    evt_manager.CallNext();
    
    //--------------------------------------------------------------------------
    // Remove event connection from object.
    //--------------------------------------------------------------------------
    obj2.PushEvent(Obj2::OBJ2_EVT_0, new Obj2::Msg(2732.2936));
    evt_manager.CallNext();
    
    evt_manager.RemoveEventConnection(obj2.GetId(), Obj2::OBJ2_EVT_0);
    obj2.PushEvent(Obj2::OBJ2_EVT_0, new Obj2::Msg(2732.2936));
    evt_manager.CallNext();

    std::cout << "End of program." << std::endl;
    
    return 0;
}

