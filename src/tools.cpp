#include <iostream>
#include "tools.h"

using Eigen::VectorXd;
using Eigen::MatrixXd;
using std::vector;

Tools::Tools() {}

Tools::~Tools() {}

VectorXd Tools::CalculateRMSE(const vector<VectorXd> &estimations,
                              const vector<VectorXd> &ground_truth) {
  /**
  TODO:
    * Calculate the RMSE here.
  */
    VectorXd rmse(4);
	rmse << 0,0,0,0;
  if (estimations.size() == 0 || estimations.size() != ground_truth.size()) {
	  cout << "Invalid estimation or ground_truth data" << endl;
	  return rmse;
  }

	//accumulate squared residuals
	for(unsigned int i=0; i < estimations.size(); ++i){

		VectorXd residual = estimations[i] - ground_truth[i];

		//coefficient-wise multiplication
		residual = residual.array()*residual.array();
		rmse += residual;
	}

	//calculate the mean
	rmse = rmse/estimations.size();

	//calculate the squared root
	rmse = rmse.array().sqrt();

  //print RMSE

    std::cout << "RMSE: " << rmse << std::endl;
	
	return rmse;
}

    float Tools::CalculateNISPerformance(const std::vector<double> &nis_values, MeasurementPackage::SensorType sensorType) {
        const float nis_radar_95 = 7.815; // 95% percent of the case should be less than this
        const float nis_lidar_95 = 5.991;

        float limit_95 = sensorType == MeasurementPackage::RADAR ? nis_radar_95 : nis_lidar_95;

        int nis_over_95 = 0;
        for(int i = 0; i < nis_values.size(); i++){
            if(nis_values[i] > limit_95){
                nis_over_95++;
            }
        }

        return (nis_over_95/(float)nis_values.size());
    }

