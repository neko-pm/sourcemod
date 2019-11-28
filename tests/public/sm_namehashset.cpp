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

#include <string>
#include <memory>

#include <sm_namehashset.h>
#include <am-allocator-policies.h>
#include <am-hashmap.h>
#include <am-string.h>
#include <sm_stringhashmap.h>

struct A {
	std::string val;

	static inline bool matches(const char *name, const A *info)
	{
		return info->val == name;
	}
	static inline uint32_t hash(const SourceMod::detail::CharsAndLength &key)
	{
		return key.hash();
	}
};

TEST(NameHashSet, Insertion) {
	SourceMod::NameHashSet<A*> set;

	std::unique_ptr<A> ptr = std::make_unique<A>();
	ptr->val = "Test";
	bool ret = set.insert("Test", ptr.get());
	ASSERT_EQ(ret, true);
}

TEST(NameHashSet, Find) {
	SourceMod::NameHashSet<A*> set;

	std::unique_ptr<A> ptr = std::make_unique<A>();
	ptr->val = "Test";
	bool ret = set.insert("Test", ptr.get());

	auto result = set.find("Test");
	EXPECT_EQ(result.found(), true);
}

TEST(NameHashSet, Contains) {
	SourceMod::NameHashSet<A*> set;

	std::unique_ptr<A> ptr = std::make_unique<A>();
	ptr->val = "Test";
	bool ret = set.insert("Test", ptr.get());

	auto result = set.contains("Test");
	EXPECT_EQ(result, true);
}

TEST(NameHashSet, Remove) {
	SourceMod::NameHashSet<A*> set;

	std::unique_ptr<A> ptr = std::make_unique<A>();
	ptr->val = "Test";
	bool ret = set.insert("Test", ptr.get());

	bool result = set.remove("Test");
	EXPECT_EQ(result, true);
	
	result = set.contains("Test");
	EXPECT_EQ(result, false);
}

TEST(NameHashSet, Clear) {
	SourceMod::NameHashSet<A*> set;

	std::unique_ptr<A> ptr = std::make_unique<A>();
	ptr->val = "Test";
	bool ret = set.insert("Test", ptr.get());

	set.clear();
	
	auto result = set.contains("Test");
	EXPECT_EQ(result, false);
}