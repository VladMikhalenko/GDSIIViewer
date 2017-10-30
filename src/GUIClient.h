/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   GUIClient.h
 * Author: Val
 *
 * Created on 2 января 2017 г., 18:44
 */

#ifndef GUICLIENT_H
#define GUICLIENT_H
#include "GDSIIDesign.h"

class GUIClient {
public:
    GUIClient();
    GUIClient(const GUIClient& orig);
    virtual ~GUIClient();
private:
    GDSIIDesign design;
};

#endif /* GUICLIENT_H */

