#pragma once

#include "TestClasses.h"

// Utility
void ObjectSizes(); // Output the sizes of test classes in bytes

// EXTERNAL
bool Test_RunCase(int testCase = 0);
bool Test_ResetEnvironment();

//////////////////////////////////////////////////////////////////////////////////
// Test Rules
//////////////////////////////////////////////////////////////////////////////////
// - Each test must be ran separately to ensure accuracy
// - Each test must be contained to its own function
// - Be careful handleing resets in between tests
