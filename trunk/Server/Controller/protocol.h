/*
 * protocol.h 
 *
 * Modified on:    $Date$
 * Last Edited By: $Author$
 * Revision:       $Revision$
 */

#ifndef PROTOCOL_H_
#define PROTOCOL_H_

#include <cstring>
#include <string>
#include <iostream>

#define P_ROBOT_INIT 1
#define P_ROBOT_UPDATE 2
#define P_OBJECT 3

#define P_NULL_PTR -1

/* the protocol converts arrays of the defined structs into byte arrays 
 * from transmission over the socket the protocol is pretty much as 
 * follows, the first byte if the type of struct in the message,
 * the second and third bytes are short representing the total
 * number of structs transmitted. Each struct is prefixed by a two byte
 * short listing the size of that particular struct instance followed by
 * the struct itself. after that each type of struct is unique.
 */

struct robotInit{
    int RID;
    int x;
    int y;
    std::string* VideoURL;
};
struct robotUpdate{
    int RID;
    int x;
    int y;
};
struct object{
    int OID;
    std::string* name;
    long color_size;
    char* color;
};

struct byteArray{
    char* array;
    int size;
};
struct readReturn{
    void* array;
    int size;
    int type;
};


void write_data(int type, void* data_, short number, byteArray* byte_ptr);


// If you get a robotInit array from this function,
// 
// You MUST delete robotInit.VideoURL when you are done with it!!!!
//
int read_data(void* array, readReturn* ret);

int readRobotInit(void* array, robotInit* &robots);

int readRobotUpdate(void* array, robotUpdate* &robots);

#endif /* PROTOCOL_H_ */

