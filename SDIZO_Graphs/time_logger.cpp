#include "time_logger.h"
#include <fstream>
#include <iomanip>

using namespace std::chrono;
using namespace std;

void time_logger::start()
{
	start_time_ = high_resolution_clock::now();
}

void time_logger::stop()
{
	stop_time_ = high_resolution_clock::now();
	calculate_time_span();
}

double time_logger::get_time_span() const
{
	return time_span_;
}

void time_logger::reset()
{
	times_.clear();
}

void time_logger::save_to_file(std::string file_name)
{
	std::ofstream fout(file_name, ios::out | ios::app);
	if (fout.is_open())
	{
		fout << std::fixed << std::setprecision(9) << mean() << endl;
	}
	fout.close();
}

double time_logger::mean()
{
	if (times_.empty())
	{
		return 0;
	}

	double sum = 0;
	for (double t : times_)
	{
		sum += t;
	}

	return sum / times_.size();
}

void time_logger::calculate_time_span()
{
	time_span_ = duration_cast<duration<double>>(stop_time_ - start_time_).count();
	times_.push_back(time_span_);
}
