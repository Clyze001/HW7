#ifndef PARSER_H
#define PARSER_H
#include "./ai.h"
#include "rjsjai.h"
#include <iostream>
#include <fstream>
using namespace std;

const char* token = "e31ef101-d948-4f0c-9f31-9d2a825d5ea6";
class Parser {
    Parser(int argc, char** argv);
    AI* doParse();

public:
    static AI* parse(int argc, char** argv);
};


class Chat_ai:public AI{
public:
    char* prompt;
    char* file_name;
    int file = 0;
    RJSJAI* ptr;
    //构造函数
    Chat_ai(){
        prompt = new char[600];
        file_name = new char[600];
        ptr = ai_create(token);
    }
    //复制构造函数
    Chat_ai(const Chat_ai* &a){
        file_name = a -> file_name;
        prompt = a -> prompt;
        file = a -> file;
        ptr = ai_create(token);
    }
    //接收
    void sendRequest(){
        ai_send(ptr, AI_TYPE_CHAT, prompt);
    }
    //输出结果
    void showResponse(){
        char* target = nullptr;
        int temp = ai_status(ptr);
        if(ai_status(ptr) == 0){
            int num = ai_result(ptr, target);
            target = new char[num];
            ai_result(ptr, target);
            if(file){
                ofstream file1;
                file1.open(file_name);
                file1 << target;
                file1.close();
            }
            else{
                ai_free(Chat_ai::ptr);
                delete[]target;
                delete[]prompt;
                delete[]file_name;
                cout << target;
            }
        }
        /*else{
            ai_free(Chat_ai::ptr);
            delete[]target;
            delete[]prompt;
            delete[]file_name;
            exit(1);
        }*/
    }
};

class Draw_ai:public AI{
public:
    char* prompt;
    char* file_name;
    int file = 0;
    RJSJAI* ptr;
    //构造函数
    Draw_ai(){
        prompt = new char[600];
        file_name = new char[600];
        file = 0;
        ptr = ai_create(token);
    }
    //复制构造函数
    Draw_ai(const Draw_ai* &a){
        file_name = a -> file_name;
        prompt = a -> prompt;
        file = a -> file;
        ptr = ai_create(token);
    }
    //接收
    void sendRequest(){
        ai_send(ptr, AI_TYPE_DRAW, prompt);
    }
    //输出结果
    void showResponse(){
        char* target = nullptr;
        int temp = ai_status(ptr);
        if(ai_status(ptr) == 0){
            int num = ai_result(ptr, target);
            target = new char[num];
            ai_result(ptr, target);
            if(file){
                ofstream file1;
                file1.open(file_name);
                file1 << target;
                file1.close();
            }
            else{
                ai_free(Draw_ai::ptr);
                delete[]target;
                delete[]prompt;
                delete[]file_name;
                cout << target;
            }
        }
        /*else{
            ai_free(Draw_ai::ptr);
            delete[]target;
            delete[]prompt;
            delete[]file_name;
            exit(1);
        }*/
    }
};


class Math_ai:public AI{
public:
    char* prompt;
    char* file_name;
    int file = 0;
    RJSJAI* ptr;
    //构造函数
    Math_ai(){
        prompt = new char[600];
        file_name = new char[600];
        file = 0;
        ptr = ai_create(token);
    }
    //复制构造函数
    Math_ai(const Math_ai* &a){
        file_name = a -> file_name;
        prompt = a -> prompt;
        file = a -> file;
        ptr = ai_create(token);
    }
    //接收
    void sendRequest(){
        ai_send(ptr, AI_TYPE_WOLFRAM, prompt);
    }
    //输出结果
    void showResponse(){
        char* target = nullptr;
        int temp = ai_status(ptr);
        if(ai_status(ptr) == 0){
            int num = ai_result(ptr, target);
            target = new char[num];
            ai_result(ptr, target);
            if(file){
                ofstream file1;
                file1.open(file_name);
                file1 << target;
                file1.close();
            }
            else{
                cout << target;
            }
            ai_free(Math_ai::ptr);
            delete[]target;
            delete[]prompt;
            delete[]file_name;
        }
        /*else{
            ai_free(Math_ai::ptr);
            delete[]target;
            delete[]prompt;
            delete[]file_name;
            exit(1);
        }*/
    }
};

AI* Parser::parse(int argc, char**argv){
    /*if(argc == 3){
        int flag = 0;
        if(argv[1][0] == '-') flag = 1;
        else flag = 2;
        if(flag == 1){
            Chat_ai* k{};
            k->prompt = argv[2];
            return k;
        }
        else if(flag == 2){
            Chat_ai* k{};
            k->prompt = argv[1];
            return k;
        }
        else exit(1);
    }*/
    if(true){
        int flag1 = 0;//记录接入接口的位置
        int type1 = 0;//0代表math，1代表draw，2代表chatgpt
        int flag2 = 0;//记录文件输入的位置
        bool if_file = 0;
        for(int i = 1; i <= argc - 1; i++){
            if(argv[i][0] == '-' && argv[i][1] == '-' && argv[i][2] == 'd'){
                flag1 = i;
                type1 = 1;
            }
            if(argv[i][0] == '-' && argv[i][1] == '-' && argv[i][2] == 'd'){
                flag1 = i;
                type1 = 0;
            }
            if(argv[i][0] == '-' && argv[i][1] == 'o'){
                flag2 = i;
                if_file = 1;
            }
            if(argv[i][0] == '-' && argv[i][1] == '-' && argv[i][2] == 'c'){
                flag1 = i;
                type1 = 2;
            }
        }
        if(type1 == 1){
            Draw_ai* k{};
            k->prompt = argv[flag1 + 1];
            if(if_file){
                k->file_name = argv[flag2 + 1];
                k->file = 1;
            }
            return k;
        }
        if(type1 == 0){
            Math_ai* k{};
            k->prompt = argv[flag1 + 1];
            if(if_file){
                k->file_name = argv[flag2 + 1];
                k->file = 1;
            }
            return k;
        }
        if(type1 == 2){
            Chat_ai* k{};
            k->prompt = argv[flag1 + 1];
            if(if_file){
                k->file_name = argv[flag2 + 1];
                k->file = 1;
            }
            return k;
        }
    }
    else exit(1);
}

#endif
