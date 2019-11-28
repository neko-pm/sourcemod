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

#include <sm_stringhashmap.h>

using namespace SourceMod;

TEST(StringHashMap, Insertion) {
	SourceMod::StringHashMap<int*> map;

	std::unique_ptr<int> ptr = std::make_unique<int>();
	*ptr = 5;
	bool ret = map.insert("ptr1", ptr.get());
	ASSERT_EQ(ret, true);
}

TEST(StringHashMap, Retrieval) {
	SourceMod::StringHashMap<int*> map;

	std::unique_ptr<int> ptr = std::make_unique<int>(5);
	bool ret = map.insert("ptr1", ptr.get());
	
	int *ptr2 = nullptr;
	ret = map.retrieve("ptr1", &ptr2);
	
	EXPECT_EQ(ptr.get(), ptr2);
	EXPECT_EQ(5, *ptr2);
}

TEST(StringHashMap, Find) {
	SourceMod::StringHashMap<int*> map;

	std::unique_ptr<int> ptr = std::make_unique<int>(5);
	bool ret = map.insert("ptr1", ptr.get());
	
	auto result = map.find("ptr1");
	EXPECT_EQ(result.found(), true);
}

TEST(StringHashMap, RemoveResult) {
	SourceMod::StringHashMap<int*> map;

	std::unique_ptr<int> ptr = std::make_unique<int>(5);
	bool ret = map.insert("ptr1", ptr.get());
	
	auto result = map.find("ptr1");
	map.remove(result);
	
	EXPECT_EQ(map.elements(), 0);
}

TEST(StringHashMap, RemoveKey) {
	SourceMod::StringHashMap<int*> map;

	std::unique_ptr<int> ptr = std::make_unique<int>(5);
	bool ret = map.insert("ptr1", ptr.get());
	
	map.remove("ptr1");
	
	EXPECT_EQ(map.elements(), 0);
}

TEST(StringHashMap, Clear) {
	SourceMod::StringHashMap<int*> map;

	std::unique_ptr<int> ptr = std::make_unique<int>(5);
	bool ret = map.insert("ptr1", ptr.get());
	
	map.clear();
	
	EXPECT_EQ(map.elements(), 0);
}