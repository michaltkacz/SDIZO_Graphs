#pragma once
#include <chrono>
#include <vector>



class time_logger
{
public:
	void start();
	void stop();
	double get_time_span() const;

	void reset();
	void save_to_file(std::string file_name);
	double mean();

private:
	std::vector<double> times_;
	std::chrono::high_resolution_clock::time_point start_time_;
	std::chrono::high_resolution_clock::time_point stop_time_;
	double time_span_ = 0;

	void calculate_time_span();
};
