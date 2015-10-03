/**
 * libnes
 * Copyright (C) 2015 David Jolly
 * ----------------------
 *
 * libnes is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * libnes is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "../include/nes.h"
#include "../include/nes_test_type.h"

#ifndef NDEBUG

namespace NES {

	namespace TEST {

		_nes_test::_nes_test(
			__in const std::string &name,
			__in nes_test_cb test,
			__in_opt void *context,
			__in_opt nes_test_cb initialize,
			__in_opt nes_test_cb uninitialize
			) :
				m_result(NES_TEST_NONE)
		{
			set(name, test, context, initialize, uninitialize);
		}

		_nes_test::_nes_test(
			__in const _nes_test &other
			) :
				m_result(other.m_result)
		{
			set(other.m_name, other.m_test, other.m_context, 
				other.m_initialize, other.m_uninitialize);
		}

		_nes_test::~_nes_test(void)
		{
			return;
		}

		_nes_test &
		_nes_test::operator=(
			__in const _nes_test &other
			)
		{
			ATOMIC_CALL_RECUR(m_lock);

			if(this != &other) {
				set(other.m_name, other.m_test, other.m_context, 
					other.m_initialize, other.m_uninitialize);
				m_result = other.m_result;
			}

			return *this;
		}

		bool 
		_nes_test::has_run(void)
		{
			ATOMIC_CALL_RECUR(m_lock);
			return (m_result != NES_TEST_NONE);
		}

		std::string 
		_nes_test::name(void)
		{
			ATOMIC_CALL_RECUR(m_lock);
			return m_name;
		}

		void 
		_nes_test::reset(void)
		{
			ATOMIC_CALL_RECUR(m_lock);
			m_result = NES_TEST_NONE;
		}

		nes_test_t 
		_nes_test::result(void)
		{
			ATOMIC_CALL_RECUR(m_lock);
			return m_result;
		}

		nes_test_t 
		_nes_test::run(
			__out_opt nes_test_t *initialized
			)
		{
			nes_test_t status = NES_TEST_SUCCESS;

			ATOMIC_CALL_RECUR(m_lock);

			m_result = NES_TEST_INCONCLUSIVE;

			if(m_initialize) {
				status = m_initialize(m_context);
			}

			if(status == NES_TEST_SUCCESS) {

				m_result = m_test(m_context);
				if(m_result > NES_TEST_MAX) {
					THROW_NES_TEST_EXCEPTION_MESSAGE(NES_TEST_EXCEPTION_UNKNOWN_RESULT,
						"res. 0x%x (%s)", m_result, NES_TEST_RESULT_STRING(m_result));
				}
			}

			if(m_uninitialize
					&& (status == NES_TEST_SUCCESS)) {
				status = m_uninitialize(m_context);
			}

			if(initialized) {
				*initialized = status;
			}

			return m_result;
		}

		void 
		_nes_test::set(
			__in const std::string &name,
			__in nes_test_cb test,
			__in_opt void *context,
			__in_opt nes_test_cb initialize,
			__in_opt nes_test_cb uninitialize
			)
		{
			ATOMIC_CALL_RECUR(m_lock);

			if(name.empty()) {
				THROW_NES_TEST_EXCEPTION(NES_TEST_EXCEPTION_INVALID_NAME_TEST);
			}

			if(!test) {
				THROW_NES_TEST_EXCEPTION(NES_TEST_EXCEPTION_UNDEFINED_CALLBACK);
			}

			m_context = context;
			m_initialize = initialize;
			m_name = name;
			m_test = test;
			m_uninitialize = uninitialize;
		}

		std::string 
		_nes_test::to_string(
			__in_opt bool verbose
			)
		{
			std::stringstream result;

			ATOMIC_CALL_RECUR(m_lock);

			if(has_run()
					&& (m_result != NES_TEST_SUCCESS)) {
				result << "[" << NES_TEST_RESULT_STRING(m_result) << "] ";
			}

			result << "<" << NES_TEST_HEADER << "::" << m_name << ">";

			if(verbose) {
				result << " (cont. 0x" << VALUE_AS_HEX(void *, m_context) 
					<< ", test. 0x" << VALUE_AS_HEX(nes_test_cb, m_test)
					<< ", init. 0x" << VALUE_AS_HEX(nes_test_cb, m_initialize)
					<< ", uninit. 0x" << VALUE_AS_HEX(nes_test_cb, m_uninitialize) 
					<< ")";
			}

			return result.str();
		}

		_nes_test_set::_nes_test_set(
			__in const std::string &name
			)
		{
			set(name);
		}

		_nes_test_set::_nes_test_set(
			__in const _nes_test_set &other
			)
		{
			set(other);
		}

		_nes_test_set::~_nes_test_set(void)
		{
			return;
		}

		_nes_test_set &
		_nes_test_set::operator=(
			__in const _nes_test_set &other
			)
		{
			ATOMIC_CALL_RECUR(m_lock);

			if(this != &other) {
				set(other);
			}

			return *this;
		}

		bool 
		_nes_test_set::contains(
			__in const std::string &name
			)
		{
			ATOMIC_CALL_RECUR(m_lock);
			return (m_set.find(name) != m_set.end());
		}

		bool 
		_nes_test_set::has_run(
			__in const std::string &name
			)
		{
			ATOMIC_CALL_RECUR(m_lock);
			return find(name)->second.has_run();
		}

		std::map<std::string, nes_test>::iterator 
		_nes_test_set::find(
			__in const std::string &name
			)
		{
			std::map<std::string, nes_test>::iterator result;

			ATOMIC_CALL_RECUR(m_lock);

			result = m_set.find(name);
			if(result == m_set.end()) {
				THROW_NES_TEST_EXCEPTION_MESSAGE(NES_TEST_EXCEPTION_NOT_FOUND,
					"%s", CHECK_STR(name));
			}

			return result;
		}

		void 
		_nes_test_set::insert(
			__in const nes_test &test
			)
		{
			ATOMIC_CALL_RECUR(m_lock);

			if(contains(test.m_name)) {
				THROW_NES_TEST_EXCEPTION_MESSAGE(NES_TEST_EXCEPTION_FOUND,
					"%s", CHECK_STR(test.m_name));
			}

			m_set.insert(std::pair<std::string, nes_test>(test.m_name, test));
		}

		std::string 
		_nes_test_set::name(void)
		{
			ATOMIC_CALL_RECUR(m_lock);
			return m_name;
		}

		void 
		_nes_test_set::remove(
			__in const std::string &name
			)
		{
			ATOMIC_CALL_RECUR(m_lock);
			m_set.erase(find(name));
		}

		void 
		_nes_test_set::remove_all(void)
		{
			ATOMIC_CALL_RECUR(m_lock);
			m_set.clear();
		}

		void 
		_nes_test_set::reset(
			__in const std::string &name
			)
		{
			ATOMIC_CALL_RECUR(m_lock);
			find(name)->second.reset();
		}

		void 
		_nes_test_set::reset_all(void)
		{
			std::map<std::string, nes_test>::iterator iter;

			ATOMIC_CALL_RECUR(m_lock);

			for(iter = m_set.begin(); iter != m_set.end(); ++iter) {
				iter->second.reset();
			}
		}

		nes_test_t 
		_nes_test_set::result(
			__in const std::string &name
			)
		{
			ATOMIC_CALL_RECUR(m_lock);
			return find(name)->second.result();
		}

		void 
		_nes_test_set::results(
			__inout size_t &success,
			__inout size_t &failure,
			__inout size_t &inconclusive
			)
		{
			nes_test_t result;
			std::map<std::string, nes_test>::iterator iter;

			ATOMIC_CALL_RECUR(m_lock);

			for(iter = m_set.begin(); iter != m_set.end(); ++iter) {

				result = iter->second.result();
				switch(result) {
					case NES_TEST_NONE:
						break;
					case NES_TEST_FAILURE:
						++failure;
						break;
					case NES_TEST_INCONCLUSIVE:
						++inconclusive;
						break;
					case NES_TEST_SUCCESS:
						++success;
						break;
					default:
						THROW_NES_TEST_EXCEPTION_MESSAGE(NES_TEST_EXCEPTION_UNKNOWN_RESULT,
							"res. 0x%x (%s)", result, NES_TEST_RESULT_STRING(result));
				}
			}
		}

		nes_test_t 
		_nes_test_set::run(
			__in const std::string &name,
			__out_opt nes_test_t *initialized
			)
		{
			ATOMIC_CALL_RECUR(m_lock);
			return find(name)->second.run(initialized);
		}

		void 
		_nes_test_set::run_all(
			__inout size_t &success,
			__inout size_t &failure,
			__inout size_t &inconclusive
			)
		{
			nes_test_t result;
			std::map<std::string, nes_test>::iterator iter;

			ATOMIC_CALL_RECUR(m_lock);

			for(iter = m_set.begin(); iter != m_set.end(); ++iter) {

				result = iter->second.run();
				switch(result) {
					case NES_TEST_NONE:
						break;
					case NES_TEST_FAILURE:
						++failure;
						break;
					case NES_TEST_INCONCLUSIVE:
						++inconclusive;
						break;
					case NES_TEST_SUCCESS:
						++success;
						break;
					default:
						THROW_NES_TEST_EXCEPTION_MESSAGE(NES_TEST_EXCEPTION_UNKNOWN_RESULT,
							"res. 0x%x (%s)", result, NES_TEST_RESULT_STRING(result));
				}
			}
		}

		void 
		_nes_test_set::set(
			__in const std::string &name
			)
		{
			ATOMIC_CALL_RECUR(m_lock);

			if(name.empty()) {
				THROW_NES_TEST_EXCEPTION(NES_TEST_EXCEPTION_INVALID_NAME_TEST_SET);
			}

			m_name = name;
			m_set.clear();
		}

		void 
		_nes_test_set::set(
			__in const _nes_test_set &other
			)
		{
			ATOMIC_CALL_RECUR(m_lock);

			m_name = other.m_name;
			m_set = other.m_set;
		}

		size_t 
		_nes_test_set::size(void)
		{
			ATOMIC_CALL_RECUR(m_lock);
			return m_set.size();
		}

		std::string 
		_nes_test_set::to_string(
			__in_opt bool verbose
			)
		{
			std::stringstream result;
			std::map<std::string, nes_test>::iterator iter;
			size_t failure = 0, inconclusive = 0, success = 0;

			ATOMIC_CALL_RECUR(m_lock);

			results(success, failure, inconclusive);

			result << "<" << NES_TEST_SET_HEADER << "::" << m_name << ">[" 
				<< size() << "] (" << success << "/" << failure << "/" 
				<< inconclusive << ")";

			for(iter = m_set.begin(); iter != m_set.end(); ++iter) {

				if(!verbose 
						&& (iter->second.result() == NES_TEST_SUCCESS)) {
					continue;
				}

				result << std::endl << "--- " << iter->second.to_string(verbose);
			}

			return result.str();
		}
	}
}

#endif // NDEBUG
