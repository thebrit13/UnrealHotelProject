// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class UNREALHOTELPROJECT_API FinanceManager
{
public:
	enum TransactionType
	{
		NIGHT,
		CLEAN
	};

	FinanceManager();
	~FinanceManager();

	void FinancialTransaction(TransactionType tt, bool add);
	int GetMoney();
private:
	const int NIGHTLY_RATE = 100;
	const int CLEANING_COST = 10;
	int Money = 0;
};
