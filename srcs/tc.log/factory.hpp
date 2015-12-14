#ifndef __tc_log_factory_h__
#define __tc_log_factory_h__

#include <tc.common/tc.hpp>
#include <tc.common/function.hpp>
#include <tc.log/encoder.hpp>
#include <tc.log/writer.hpp>

namespace tc { 
namespace log {

/*!
 * configure in code level
 * registry use factory 
 * 1. factory register
 * 2. registry load config from file
 * 3. registry alloc instances by using factory
 */
	class factory {
	public:
		std::shared_ptr<tc::log::encoder> create_encoder(const std::string& name
			, const std::string& param);

		std::shared_ptr<tc::log::writer> create_writer(const std::string& name
			, const std::string& param);

		void register_encoder(const std::string& name
			, const tc::function< std::shared_ptr<tc::log::encoder> (const std::string& param) >& encoder_create);
		void register_writer(const std::string& name
			, const tc::function< std::shared_ptr<tc::log::writer> (const std::string& param) >& writer_create);

		template < typename T >
		class creater_no_param{
		public:
			std::shared_ptr<T> operator()(const std::string&) {
				return std::shared_ptr<T>( new T());
			}
		};
public:
	static factory& instance(void);
private:
	factory( void );
	~factory( void );
	
private:
	std::map< std::string 
		, tc::function< std::shared_ptr<tc::log::encoder> ( const std::string& param ) > 
		> _encoders;
	std::map< std::string 
		, tc::function< std::shared_ptr<tc::log::writer> ( const std::string& param ) > 
		> _writers;
};


}}

#endif
