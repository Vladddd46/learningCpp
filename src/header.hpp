#pragma once
#include "Vector.hpp"
#include "List.hpp"
#include "SharedPtr.hpp"
#include "BinaryTree.hpp"
#include "LinearAllocator.hpp"
#include <limits>
#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <deque>
#include <stdio.h>
#include <cassert>
#include <chrono>
#include <memory>

// Vector tests.
void pushBackTest();
void eraseTest();
void copyConstructorTest();
void pushBackTimeTest();
void insertTimeTest();

// List tests.
void pushBackListTest();
void pushFrontListTest();
void popFrontListTest();
void popBackListTest();
void frontListTest();
void backListTest();
void insertListTest();

