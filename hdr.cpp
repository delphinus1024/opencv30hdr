#include <opencv2/photo.hpp>
#include "opencv2/imgcodecs.hpp"
#include <opencv2/highgui.hpp>
#include <vector>
#include <iostream>
#include <fstream>

using namespace cv;
using namespace std;

void loadExposureSeq(String, vector<Mat>&, vector<float>&);

int main(int, char**argv)
{
    vector<Mat> images;
    vector<float> times;
    loadExposureSeq(argv[1], images, times);

	
    Mat response_dev;
    Ptr<CalibrateDebevec> calibrate_dev = createCalibrateDebevec();
    calibrate_dev->process(images, response_dev, times);

	cout << response_dev << endl;
	
	/*
    Mat response_rob;
    Ptr<CalibrateRobertson> calibrate_rob = createCalibrateRobertson();
    calibrate_rob->process(images, response_rob, times);

	cout << "response_rob" << endl;
	cout << response_rob << endl;
	*/
	
    Mat hdr;
    
    Ptr<MergeDebevec> merge_debevec = createMergeDebevec();
	merge_debevec->process(images, hdr, times, response_dev);
    //merge_debevec->process(images, hdr, times, response_rob);
	
	
	{
	    Mat ldr_drago;
	    
	    Ptr<TonemapDrago> tonemap_drago = createTonemapDrago(2.0f,1.0f,0.85f);
	    tonemap_drago->process(hdr, ldr_drago);
	    imwrite("ldr_drago.png", ldr_drago * 255);
	}
	
	{
	    Mat ldr_durand;
		
	    Ptr<TonemapDurand> tonemap_durand = createTonemapDurand(2.0f,4.0f,1.0f,2.0f,2.0f);
	    tonemap_durand->process(hdr, ldr_durand);
	    imwrite("ldr_durand.png", ldr_durand * 255);
	}
	
	{
	    Mat ldr_mantiuk;
		
	    Ptr<TonemapMantiuk> tonemap_mantiuk = createTonemapMantiuk(2.2f,0.7f,1.0f);
	    tonemap_mantiuk->process(hdr, ldr_mantiuk);
	    imwrite("ldr_mantiuk.png", ldr_mantiuk * 255);
	}
	
	{
	    Mat ldr_reinhard;	
		
	    Ptr<TonemapReinhard> tonemap_reinhard = createTonemapReinhard(1.0f,0.0f,0.2f,0.0f);
	    tonemap_reinhard->process(hdr, ldr_reinhard);
	    imwrite("ldr_reinhard.png", ldr_reinhard * 255);
	}
	
	{
	    Mat fusion;
	    Ptr<MergeMertens> merge_mertens = createMergeMertens(1.0f,1.0f,1.0f);
	    merge_mertens->process(images, fusion);
	    imwrite("fusion_111.png", fusion * 255);

	    merge_mertens = createMergeMertens(0.0f,1.0f,1.0f);
	    merge_mertens->process(images, fusion);
	    imwrite("fusion_011.png", fusion * 255);

	    merge_mertens = createMergeMertens(1.0f,0.0f,1.0f);
	    merge_mertens->process(images, fusion);
	    imwrite("fusion_101.png", fusion * 255);

	    merge_mertens = createMergeMertens(1.0f,1.0f,0.0f);
	    merge_mertens->process(images, fusion);
	    imwrite("fusion_110.png", fusion * 255);
	}

    //imwrite("hdr.hdr", hdr);

    return 0;
}

void loadExposureSeq(String path, vector<Mat>& images, vector<float>& times)
{
    path = path + std::string("/");
    ifstream list_file((path + "list.txt").c_str());
    string name;
    float val;
    while(list_file >> name >> val) {
        Mat img = imread(path + name);
        images.push_back(img);
        times.push_back(1 / val);
    }
    list_file.close();
}
   
