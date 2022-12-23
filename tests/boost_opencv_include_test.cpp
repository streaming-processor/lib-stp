#include <catch2/catch_test_macros.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <boost/multiprecision/cpp_int.hpp>

using namespace boost::multiprecision;

TEST_CASE("Mat object is created ", "[createImage]")
{
    cv::Mat img(10, 2, CV_32FC1);
    REQUIRE(img.rows==10);
    REQUIRE(img.cols==2);

}


int128_t boost_product(long long A, long long B)
{
    int128_t ans = (int128_t)A * B;
    return ans;
}   
    

TEST_CASE("Boost product", "[boost_product")
{
    long long first = 987456;
    long long second = 74598;
     
    REQUIRE(boost_product(first, second) == 73662242688);

}

