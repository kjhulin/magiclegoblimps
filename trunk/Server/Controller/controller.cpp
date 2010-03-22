/*
 * controller.cpp
 *
 * Modified on:    $Date$
 * Last Edited By: $Author$
 * Revision:       $Revision$
 */

#include <iostream>

#include "controller.h"

controller::controller(boost::asio::io_service& io_service) 
    : io_(io_service)
{
    std::cout << "In controller constructor\n";
    
    db = new DbManager();

    robots = new Vector_ts<Robot*>();
    objs = new Vector_ts<Object*>();

    admin = new AdminHandler;
    adminSrv = new TcpServer(io_service, 10000, admin);

    robo = new RobotHandler(robots);
    roboSrv = new TcpServer(io_service, 9999, robo);

    vids = new VideoHandler(robots, objs);
    vidsSrv = new TcpServer(io_service, 20000, vids);

}

controller::~controller() {
    delete db;

    delete admin;
    delete adminSrv;

    delete robo;
    delete roboSrv;
    delete robots;

    delete vids;
    delete vidsSrv;
}

int controller::testdb() {
    db->printRequests();
    std::cout << "\n-----------------------------\n";

    std::map<int, boost::rational<int> > *demand = new demand_t();
    db->getRequests(demand);

    demand_t::iterator iter;
    for (iter = demand->begin(); iter != demand->end(); ++iter) {
        std::cout << "Demand for " << iter->first << ": " << iter->second << "\n";
    }

    delete demand;

    return 0;
}


/* vi: set tabstop=4 expandtab shiftwidth=4 softtabstop=4: */