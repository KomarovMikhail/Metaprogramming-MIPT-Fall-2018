#include <iostream>
#include "patterns.h"

int main() {
    auto *proxyHandler = new Handler<Proxy>();
    auto *proxySender = new Sender<Proxy>(proxyHandler);
    proxySender->action();
    delete proxyHandler;
    delete proxySender;

    auto observerHandler = new Handler<Observer>();
    auto observerSender = new Sender<Observer>(observerHandler);
    observerSender->action();
    delete observerHandler;
    delete observerSender;

    auto mediatorHandler = new Handler<Mediator>();
    auto mediatorSender = new Sender<Mediator>(mediatorHandler);
    mediatorSender->action();
    delete mediatorHandler;
    delete mediatorSender;
}