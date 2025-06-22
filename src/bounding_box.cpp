#include "bounding_box.hpp"


std::vector<Vector> BoundingBox::getBoundingBox(const cv::Mat& image) {
    std::vector<Vector> boundingBox;

    cv::Mat imageGray, imageBinary;
    
    // Converte para escala de cinza
    cv::cvtColor(image, imageGray, cv::COLOR_BGR2GRAY);

    // Binariza a imagem (fundo escuro, imagem branca)
    cv::threshold(imageGray, imageBinary, 127, 255, cv::THRESH_BINARY);

    // Encontra contornos
    std::vector<std::vector<cv::Point>> contours;
    cv::findContours(imageBinary, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

    // Assume o maior contorno
    double maxArea = 0;
    int maxIndex = 0;

    for (size_t i = 0; i < contours.size(); ++i) {
        double area = cv::contourArea(contours[i]);
        if (area > maxArea) {
            maxArea = area;
            maxIndex = i;
        }
    }

    // Converte para vetor de Ponto
    if (maxIndex >= 0) {
        for (const auto& pt : contours[maxIndex]) {
            boundingBox.emplace_back(Vector(pt.x, pt.y));
        }
    }

    return boundingBox;
}