/**
 * vim: set ts=4 :
 * =============================================================================
 * SourceMod Test Suite
 * Copyright (C) 2019 AlliedModders LLC.  All rights reserved.
 * =============================================================================
 *
 * This program is free software; you can redistribute it and/or modify it under
 * the terms of the GNU General Public License, version 3.0, as published by the
 * Free Software Foundation.
 * 
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * As a special exception, AlliedModders LLC gives you permission to link the
 * code of this program (as well as its derivative works) to "Half-Life 2," the
 * "Source Engine," the "SourcePawn JIT," and any Game MODs that run on software
 * by the Valve Corporation.  You must obey the GNU General Public License in
 * all respects for all other code used.  Additionally, AlliedModders LLC grants
 * this exception to all derivative works.  AlliedModders LLC defines further
 * exceptions, found in LICENSE.txt (as of this writing, version JULY-31-2007),
 * or <http://www.sourcemod.net/license.php>.
 *
 * Version: $Id$
 */

#include <gtest/gtest.h>

#include <sm_memtable.h>

TEST(BaseMemTable, Size) {
	
	constexpr int size = 1024;
	BaseMemTable table(size);
	
	EXPECT_EQ(table.GetMemUsage(), size);
	EXPECT_EQ(table.GetActualMemUsed(), 0);
	
	int* mem = nullptr;
	int index = table.CreateMem(sizeof(int), (void**)&mem);

	EXPECT_EQ(table.GetActualMemUsed(), sizeof(int));
	EXPECT_NE(mem, nullptr);
	
	table.Reset();
	EXPECT_EQ(table.GetActualMemUsed(), 0);
}

TEST(BaseMemTable, Address) {
	constexpr int size = 1024;
	BaseMemTable table(size);
	
	int* mem = nullptr;
	int index = table.CreateMem(sizeof(int), (void**)&mem);
	*mem = 52;
	
	ASSERT_GT(index, -1);
	
	int *addr = (int*)table.GetAddress(index);
	ASSERT_EQ(addr, mem);
	
	EXPECT_EQ(*mem, *addr);
}

TEST(BaseStringTable, Basic) {
	constexpr int size = 1024;
	BaseStringTable table(size);
	
	constexpr const char *inputstr = "eeeegggggsssss....";
	int index = table.AddString(inputstr);
	ASSERT_GT(index, -1);
	
	const char *str = table.GetString(index);
	EXPECT_STREQ(inputstr, str);
	
	index = table.AddString("egg.");
	EXPECT_GT(index, 0);
}
