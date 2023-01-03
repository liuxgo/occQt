/*
 * @Author: 刘欣 liu.xin@iungoprint.com
 * @Date: 2023-01-01 19:49:50
 * @LastEditors: 刘欣 liu.xin@iungoprint.com
 * @LastEditTime: 2023-01-01 20:03:28
 * @Description:
 * Copyright (c) 2023 by iUNGO, All Rights Reserved.
 */
/*
 *    Copyright (c) 2018 Shing Liu All Rights Reserved.
 *
 *           File : main.cpp
 *         Author : Shing Liu(eryar@163.com)
 *           Date : 2018-01-08 20:00
 *        Version : OpenCASCADE7.2.0 & Qt5.7.1
 *
 *    Description : OpenCASCADE with Qt demo.
 */

#include "occQt.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    occQt w;
    w.show();

    return a.exec();
}
