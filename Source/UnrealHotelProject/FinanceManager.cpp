// Fill out your copyright notice in the Description page of Project Settings.


#include "FinanceManager.h"

FinanceManager::FinanceManager()
{
}

FinanceManager::~FinanceManager()
{
}

void FinanceManager::FinancialTransaction(TransactionType tt, bool add)
{
	switch (tt)
	{
		case FinanceManager::NIGHT:
			add ? Money += NIGHTLY_RATE : Money -= NIGHTLY_RATE;
			break;
		case FinanceManager::CLEAN:
			add ? Money += CLEANING_COST : Money -= CLEANING_COST;
			break;
		default:
			break;
	}
}

int FinanceManager::GetMoney()
{
	return Money;
}
