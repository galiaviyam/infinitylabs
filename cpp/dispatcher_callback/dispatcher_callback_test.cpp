/****************************************/
/*                                      */   
/*   Developer: Gali Aviyam             */
/*   Project:   Dispatcher - Callback   */
/*   Date:      09/06/23                */
/*   Reviewer:  Itay                    */
/*                                      */
/****************************************/

#include <iostream>
#include "dispatcher_callback.hpp"

class ViewWindow
{
public:
    void HandleEvent(int event)
    {
        std::cout << "ViewWindow received event: " << event << std::endl;
    }

    void Close()
    {
        std::cout << "ViewWindow is closing" << std::endl;
    }
};

class DataModel
{
public:
    void Update(int event)
    {
        std::cout << "DataModel received event: " << event << std::endl;
    }

    void Close()
    {
        std::cout << "DataModel is closing" << std::endl;
    }
};

class ControlWindow
{
public:
    void ProcessEvent(int event)
    {
        std::cout << "ControlWindow received event: " << event << std::endl;
    }

    void Close()
    {
        std::cout << "ControlWindow is closing" << std::endl;
    }
};

int main()
{
    using namespace ilrd;

    Dispatcher<int> dispatcher;

    // Create instances of the classes
    ViewWindow viewWindow;
    DataModel dataModel;
    ControlWindow controlWindow;

    // Create callbacks for each class
    Callback<ViewWindow, int> viewCallback(&viewWindow, &ViewWindow::HandleEvent, &ViewWindow::Close);
    Callback<DataModel, int> dataCallback(&dataModel, &DataModel::Update, &DataModel::Close);
    Callback<ControlWindow, int> controlCallback(&controlWindow, &ControlWindow::ProcessEvent, &ControlWindow::Close);

    // Register callbacks with the dispatcher
    dispatcher.Register(&viewCallback);
    dispatcher.Register(&dataCallback);
    dispatcher.Register(&controlCallback);

    // Test scenarios
    std::cout << "Broadcast to one observer" << std::endl;
    dispatcher.NotifyAll(1);
    std::cout << std::endl;

    std::cout << "Broadcast to two observers" << std::endl;
    dispatcher.NotifyAll(2);
    std::cout << std::endl;

    std::cout << "Broadcast to three observers" << std::endl;
    dispatcher.NotifyAll(3);
    std::cout << std::endl;

    std::cout << "Remove one observer during broadcast" << std::endl;
    dispatcher.Unregister(&dataCallback);
    dispatcher.NotifyAll(4);
    std::cout << std::endl;

    std::cout << "Remove all observers during broadcast" << std::endl;
    dispatcher.Unregister(&viewCallback);
    dispatcher.Unregister(&controlCallback);
    dispatcher.NotifyAll(5);
    std::cout << std::endl;

    std::cout << "Add observer during broadcast" << std::endl;
    dispatcher.Register(&viewCallback);
    dispatcher.NotifyAll(6);
    std::cout << std::endl;

    std::cout << "Add two observers during broadcast" << std::endl;
    dispatcher.Register(&controlCallback);
    dispatcher.Register(&dataCallback);
    dispatcher.NotifyAll(7);
    std::cout << std::endl;

    return 0;
}