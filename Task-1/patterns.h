#ifndef METATASK1_PATTERNS_H
#define METATASK1_PATTERNS_H

#include <iostream>
#include <list>
#include <array>
#include <vector>

template <class P>
class Handler;

class Receiver;

class IReceiver;

class IObserver {
public:
    virtual void update(const Receiver&) = 0;
};

class IMediator {
public:
    virtual void send(std::string const& message, IReceiver* receiver) const = 0;
};

//class IColleague {
//protected:
//    IMediator* _mediator;
//public:
//    explicit IColleague(IMediator* mediator);
//    virtual void send(std::string const& message) = 0;
//    virtual void notify(std::string const& message) = 0;
//};

class IPattern {
    virtual void action() = 0;
};

class IReceiver {
protected:
    IMediator* _mediator;
public:
    IReceiver() : _mediator(nullptr) {};
    virtual void call() = 0;

    explicit IReceiver(IMediator* mediator);
    virtual void send(std::string const& message) = 0;
    virtual void notify(std::string const& message, unsigned long i) = 0;
};

class Receiver: public IReceiver {
public:
    Receiver();
    void call() override;  // for Proxy

    void changeState(int newState);  // for Observer
    int getState() const;  // for Observer
    void addObserver(IObserver& observer);  // for Observer
    void removeObserver(IObserver& observer);  // for Observer

    explicit Receiver(IMediator* mediator);  // for Mediator
    void send(std::string const& message) override;  // for Mediator
    void notify(std::string const& message, unsigned long i) override;  // for Mediator

private:
    int _state = 0;  // for Observer
    std::list<IObserver*> _observers;  // for Observer
    void _notify();  // for Observer

};

class Proxy: public IPattern, public IReceiver {
public:
    Proxy();
    ~Proxy();
    void call() override;
    void action() override;

    void send(std::string const& message) override {/*Empty method*/};
    void notify(std::string const& message, unsigned long i) override {/*Empty method*/};

private:
    IReceiver *receiver;
};

class Observer: public IPattern, public IObserver {
public:
    void update(const Receiver& receiver) override;
    void action() override;
};

class Mediator: public IPattern, public IMediator {
protected:
    std::vector<IReceiver*> receivers;
public:
    explicit Mediator(unsigned long capacity);
    Mediator();
    void setReceiver(IReceiver* receiver, unsigned long pos);
    void send(std::string const& message, IReceiver* receiver) const override;
    void action() override;
};

template <class P>
class Sender {
private:
    Handler<P> *handler;
public:
    explicit Sender<P>(Handler<P> *h) : handler(h) {};
    void action() {
        handler->action();
    }
};

template <class P> // IPattern object
class Handler {
public:
    void action() {
        _pattern.action();
    }
private:
    P _pattern;
};


#endif //METATASK1_PATTERNS_H
