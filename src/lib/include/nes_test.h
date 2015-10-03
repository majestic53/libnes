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

#ifndef NDEBUG
#ifndef NES_TEST_H_
#define NES_TEST_H_

namespace NES {

	namespace TEST {

		typedef enum {
			NES_TEST_NONE = 0,
			NES_TEST_FAILURE,
			NES_TEST_INCONCLUSIVE,
			NES_TEST_SUCCESS,
		} nes_test_t;

		#define NES_TEST_MAX NES_TEST_SUCCESS

		static const std::string NES_TEST_RESULT_STR[] = {
			"UNRUN", "FAILURE", "INCONCLUSIVE", "SUCCESS",
			};

		#define NES_TEST_RESULT_STRING(_TYPE_) \
			((_TYPE_) > NES_TEST_MAX ? UNKNOWN : \
			CHECK_STR(NES_TEST_RESULT_STR[_TYPE_]))

		typedef nes_test_t (*nes_test_cb)(
			__in void *context
			);

		typedef class _nes_test {

			public:

				_nes_test(
					__in const std::string &name,
					__in nes_test_cb test,
					__in_opt void *context = NULL,
					__in_opt nes_test_cb initialize = NULL,
					__in_opt nes_test_cb uninitialize = NULL
					);

				_nes_test(
					__in const _nes_test &other
					);

				virtual ~_nes_test(void);

				_nes_test &operator=(
					__in const _nes_test &other
					);

				bool has_run(void);

				std::string name(void);

				void reset(void);

				nes_test_t result(void);

				nes_test_t run(
					__out_opt nes_test_t *initialized = NULL
					);

				void set(
					__in const std::string &name,
					__in nes_test_cb test,
					__in_opt void *context = NULL,
					__in_opt nes_test_cb initialize = NULL,
					__in_opt nes_test_cb uninitialize = NULL
					);

				virtual std::string to_string(
					__in_opt bool verbose = false
					);

			protected:

				friend class _nes_test_set;

				void *m_context;

				nes_test_cb m_initialize, m_test, m_uninitialize;

				std::string m_name;

				nes_test_t m_result;

			private:

				std::recursive_mutex m_lock;

		} nes_test, *nes_test_ptr;

		typedef class _nes_test_set {

			public:

				_nes_test_set(
					__in const std::string &name
					);

				_nes_test_set(
					__in const _nes_test_set &other
					);

				virtual ~_nes_test_set(void);

				_nes_test_set &operator=(
					__in const _nes_test_set &other
					);

				bool contains(
					__in const std::string &name
					);

				bool has_run(
					__in const std::string &name
					);

				void insert(
					__in const nes_test &test
					);

				std::string name(void);

				void remove(
					__in const std::string &name
					);

				void remove_all(void);

				void reset(
					__in const std::string &name
					);

				void reset_all(void);

				nes_test_t result(
					__in const std::string &name
					);

				void results(
					__inout size_t &success,
					__inout size_t &failure,
					__inout size_t &inconclusive
					);

				nes_test_t run(
					__in const std::string &name,
					__out_opt nes_test_t *initialized = NULL
					);

				void run_all(
					__inout size_t &success,
					__inout size_t &failure,
					__inout size_t &inconclusive
					);

				void set(
					__in const std::string &name
					);

				void set(
					__in const _nes_test_set &other
					);

				size_t size(void);

				virtual std::string to_string(
					__in_opt bool verbose = false
					);

			protected:

				std::map<std::string, nes_test>::iterator find(
					__in const std::string &name
					);

				std::string m_name;

				std::map<std::string, nes_test> m_set;

			private:

				std::recursive_mutex m_lock;

		} nes_test_set, *nes_test_set_ptr;
	}
}

#endif // NES_TEST_H_
#endif // NDEBUG
