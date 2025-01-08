// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Containers/UnrealString.h"
#include "Logging/LogMacros.h"

// extern 전역변수를 따로 정의를 하지 않으면 문제가 생길 수 있음.
// 그 후에 cpp에 Define 해준다.
DECLARE_LOG_CATEGORY_EXTERN(LogCMS, Log, All);
