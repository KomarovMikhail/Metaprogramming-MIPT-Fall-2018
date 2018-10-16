#include "patterns.h"


Receiver::Receiver() : IReceiver() {}

Receiver::Receiver(IMediator *mediator) : IReceiver(mediator) {}

void Receiver::call() {
    std::cout << "Called receiver's method\n";
}

void Receiver::changeState(int newState) {
    _state = newState;
    _notify();
}

int Receiver::getState() const {
    return _state;
}

void Receiver::_notify() {
    for(auto& observer: _observers)
    {
        observer->update(*this);
    }
}

void Receiver::addObserver(IObserver &observer) {
    _observers.push_back(&observer);
}

void Receiver::removeObserver(IObserver &observer) {
    _observers.remove(&observer);
}

void Receiver::send(std::string const &message) {
    _mediator->send(message, this);
}

void Receiver::notify(std::string const &message, unsigned long i) {
    std::cout << "Receiver " << i << " got message: " << message << std::endl;
}

Proxy::Proxy() {
    receiver = new Receiver();
}

Proxy::~Proxy() {
    delete receiver;
}

void Proxy::call() {
    receiver->call();
}

void Proxy::action() {
    // tests Proxy pattern
    call();
}

void Observer::update(const Receiver &receiver) {
    std::cout << "State has been changed. New state: " << receiver.getState() << std::endl;
}

void Observer::action() {
    // tests Observer pattern
    auto receiver = new Receiver();

    receiver->addObserver(*this);
    receiver->changeState(1);

    delete receiver;
}

IReceiver::IReceiver(IMediator *mediator) : _mediator(mediator) {}

Mediator::Mediator(unsigned long capacity) {
    receivers.resize(capacity);
}

Mediator::Mediator() {
    receivers.resize(10);
}

void Mediator::setReceiver(IReceiver *receiver, unsigned long pos) {
    if (pos < receivers.size()) {
        receivers[pos] = receiver;
    } else {
        throw std::out_of_range("Wrong receiver index");
    }
}

void Mediator::send(std::string const &message, IReceiver *receiver) const {
    for (unsigned long i = 0; i < receivers.size(); ++i) {
        if (receivers[i] == receiver) {
            receivers[i]->notify(message, i);
            break;
        }
    }
}

void Mediator::action() {
    // tests Mediator pattern

    Receiver receiver1(this);
    Receiver receiver2(this);

    this->setReceiver(&receiver1, 1);
    this->setReceiver(&receiver2, 3);

    receiver1.send("Receiver 1 message");
    receiver2.send("Receiver 2 message");
}


