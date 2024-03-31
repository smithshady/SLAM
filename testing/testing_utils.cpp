#include <Eigen/Dense>
#include <vector>
#include <fstream>
#include <random>
#include <iostream>
#include <ctime>

#define NUM_POINTS          (3000)
#define RANGE               (12)
#define TX                  (0)
#define TY                  (0)
#define TZ                  (0)
#define ROTATIONX           (16 * M_PI / 180)
#define ROTATIONY           (2 * M_PI / 180)

int main() {

    // Generate xyz points
    std::vector<Eigen::Vector3d> points;
    std::default_random_engine generator(std::time(nullptr));
    std::uniform_real_distribution<double> distribution(-RANGE, RANGE);
    for (int i = 0; i < NUM_POINTS; ++i) {
        Eigen::Vector3d point(distribution(generator), distribution(generator), distribution(generator));
        points.push_back(point);
    }

    // // Generate star xyz points
    // std::vector<Eigen::Vector3d> points;
    // for (int i = 0; i < NUM_POINTS; ++i) {
    //     double angle = 0.001 + 2 * M_PI * i / NUM_POINTS;
    //     double radius = (i % 2 == 0) ? 1.0 : 0.5; // alternate between two radii to form the star shape
    //     double x = radius * cos(angle);
    //     double y = radius * sin(angle);
    //     double z = 1.1; // assuming 2D star
    //     Eigen::Vector3d point(x,y,z);
    //     points.push_back(point);
    // }

    // Save to an xyz file in data folder
    std::ofstream outFile("../points.xyz");
    for (const auto& point : points) {
        outFile << point[0] << " " << point[1] << " " << point[2] << "\n";
    }
    outFile.close();

    // Create transformation objects
    Eigen::Matrix3d rotation_X = Eigen::AngleAxisd(ROTATIONX, Eigen::Vector3d::UnitX()).toRotationMatrix();
    Eigen::Matrix3d rotation_Y = Eigen::AngleAxisd(ROTATIONY, Eigen::Vector3d::UnitY()).toRotationMatrix();
    auto rotation = rotation_X * rotation_Y;
    Eigen::Vector3d translation(TX, TY, TZ);

    // Print transformation
    Eigen::Transform<double, 3, Eigen::Affine> transform = Eigen::Translation3d(translation) * rotation;
    std::cout << std::setprecision(3) << "Transformation Matrix:" << std::endl << transform.matrix() << std::endl;

    // Generate transformed xyz points
    std::vector<Eigen::Vector3d> transformedPoints;
    for (const auto& point : points) {
        Eigen::Vector3d transformedPoint = rotation * point + translation;
        transformedPoints.push_back(transformedPoint);
    }

    // Save to another xyz file
    std::ofstream outFileTransformed("../points_transformed.xyz");
    for (const auto& point : transformedPoints) {
        outFileTransformed << point[0] << " " << point[1] << " " << point[2] << "\n";
    }
    outFileTransformed.close();

    return 0;
}
