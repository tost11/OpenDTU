// SPDX-License-Identifier: GPL-2.0-or-later
/*
 * Copyright (C) 2022 - 2023 Thomas Basler and others
 */
#include "Parser.h"

Parser::Parser()
{
    _xSemaphore = xSemaphoreCreateMutex();
    HOY_SEMAPHORE_GIVE(); // release before first use
}


void Parser::beginAppendFragment()
{
    HOY_SEMAPHORE_TAKE();
}

void Parser::endAppendFragment()
{
    HOY_SEMAPHORE_GIVE();
}