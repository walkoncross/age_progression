#include "warp.hpp"

#include "asmmodel.h"
#include "tracker/FaceTracker.hpp"

using namespace cv;
using namespace std;
using namespace StatModel;
using namespace FACETRACKER;


class FakeFaceDet : public FACETRACKER::FDet
{
public:
    FakeFaceDet(cv::Rect r) : FDet()
    {
        rect = r;
    }
    virtual ~FakeFaceDet() { }
    virtual Rect Detect(Mat im)
    {
        Rect res = FDet::Detect(im);
        if(res.width == 0 || res.height == 0)
            return rect;
        else
            return res;
    }
    cv::Rect rect;
};



//range is [0.0 .. 1.0]
void HSVtoRGB( float& r, float &g, float &b, float h, float s, float v )
{
    int i;
    float f, p, q, t;

    if( s == 0 ) {
        // achromatic (grey)
        r = g = b = v;
        return;
    }

    h *= 6.0;            // sector 0 to 5
    i = floor( h );
    f = h - i;          // factorial part of h
    p = v * ( 1 - s );
    q = v * ( 1 - s * f );
    t = v * ( 1 - s * ( 1 - f ) );

    switch( i ) {
        case 0:
            r = v; g = t; b = p;
            break;
        case 1:
            r = q; g = v; b = p;
            break;
        case 2:
            r = p; g = v; b = t;
            break;
        case 3:
            r = p; g = q; b = v;
            break;
        case 4:
            r = t; g = p; b = v;
            break;
        default:        // case 5:
            r = v; g = p;b = q;
            break;
    }
}


Mat showASMpts(Mat img)
{
    imshow("img", img);
    waitKey(0);

    Rect faceRect = findFace(img);

    ASMModel asmDetector;
    string asmFname = "./3rdparty/asmlib-opencv-read-only/data/muct76.model";
    asmDetector.loadFromFile(asmFname);
    vector<Rect> faces; faces.push_back(faceRect);
    int verboseL = 0;
    vector < ASMFitResult > fitResult = asmDetector.fitAll(img, faces, verboseL);
    vector<Point> points;
    fitResult[0].toPointList(points);

    Mat toDraw = img.clone();
    for(size_t i = 0; i < points.size(); i++)
    {
        circle(toDraw, points[i], 2, Scalar::all(255));
    }

    return toDraw;
}


Mat drawPtsOnImg(Mat img, vector<Point2d> pts)
{
    Mat buf = img.clone();
    for(size_t i = 0; i < pts.size(); i++)
    {
        circle(buf, pts[i], 2, Scalar(255, 0, 0));
    }
    return buf;
}


Mat drawPtsOnImg(Mat img, vector<Point> pts)
{
    Mat buf = img.clone();
    for(size_t i = 0; i < pts.size(); i++)
    {
        circle(buf, pts[i], 2, Scalar(255, 0, 0));
    }
    return buf;
}


Rect boundingRect(vector<Point2d> pts)
{
    int minx = 10000, miny = 10000, maxx = 0, maxy = 0;
    for(size_t j = 0; j < pts.size(); j++)
    {
        int x = pts[j].x, y = pts[j].y;
        minx = min(minx, x); miny = min(miny, y);
        maxx = max(maxx, x); maxy = max(maxy, y);
    }
    Rect r(minx, miny, maxx-minx, maxy-miny);
    return r;
}


Rect findFace(Mat img)
{
    string profileCascadeFname =
            "./3rdparty/asmlib-opencv-read-only/data/haarcascade_profileface.xml";
    string frontalCascadeFname =
            "./3rdparty/asmlib-opencv-read-only/data/haarcascade_frontalface_alt.xml";
    CascadeClassifier frontal(frontalCascadeFname);
    CascadeClassifier profile(profileCascadeFname);

    Rect frontR = runCascade(img, frontal);

    if(frontR == Rect())
    {
        Rect profileR = runCascade(img, profile);
        if(profileR == Rect())
        {
            return Rect(0, 0, img.cols, img.rows);
        }
        else
        {
            return profileR;
        }
    }
    else
    {
        return frontR;
    }
}


Rect runCascade(Mat img, CascadeClassifier cc)
{
    vector<Rect> objects;
    vector<int> rejectLevels;
    vector<double> levelWeights;
    double scaleFactor=1.1;
    int minNeighbours=3, flags=0;
    Size minSize=Size(), maxSize=Size();
    bool outputRejectLevels=true;
    cc.detectMultiScale(img, objects, rejectLevels, levelWeights, scaleFactor,
                        minNeighbours, flags, minSize, maxSize, outputRejectLevels);

    if(objects.size() == 0)
    {

        return Rect();
    }
    else
    {
        return objects[0];
    }
}


//pair<cv::Mat, cv::Mat> findOpticalFlow(Mat a, Mat b)
cv::Mat findOpticalFlow(Mat a, Mat b)
{
    Mat flowAb, flowBa;
    //use SimpleFlow method
    //calcOpticalFlowSF(a, b, flowAb,
    //                  3, 2, 4, 4.1, 25.5, 18, 55.0, 25.5, 0.35, 18, 55.0, 25.5, 10);
    Mat aGray, bGray;
    cvtColor(a, aGray, CV_BGR2GRAY);
    cvtColor(b, bGray, CV_BGR2GRAY);
    //calcOpticalFlowFarneback(aGray, bGray, flowAb, 0.5, 3, 15, 3, 5, 1.2, 0);
    double pyr_scale = 0.5;
    int levels = 4;
    int winSize = 32;
    int iterations = 1;
    int poly_n = 7;
    double poly_sigma = 1.5;
    int flags = OPTFLOW_FARNEBACK_GAUSSIAN;
    calcOpticalFlowFarneback(aGray, bGray, flowAb, pyr_scale, levels, winSize, iterations,
                             poly_n, poly_sigma, flags);

    //visualize
    Mat flowViz(flowAb.rows, flowAb.cols, CV_8UC3);
    for(int x = 0; x < flowAb.cols; x++)
    {
        for(int y = 0; y < flowAb.rows; y++)
        {
            Vec3b& v = flowViz.at<Vec3b>(y, x);
            Point2f& f = flowAb.at<Point2f>(y, x);
            double angle = atan2(f.y, f.x)/(2*CV_PI)+0.5;
            double rad = sqrt(f.x*f.x+f.y*f.y);
            float r, g, b;
            HSVtoRGB(r, g, b, angle, rad/8.0, 1.0);
            v[0] = saturate_cast<uchar>(b*255.0);
            v[1] = saturate_cast<uchar>(g*255.0);
            v[2] = saturate_cast<uchar>(r*255.0);
        }
    }

    imshow("viz flow", flowViz);
    waitKey(0);


    //and backwards
    //calcOpticalFlowSF(b, a, flowBa,
    //                  3, 2, 4, 4.1, 25.5, 18, 55.0, 25.5, 0.35, 18, 55.0, 25.5, 10);
    //return pair<Mat, Mat> (flowAb, flowBa);
    return flowAb;
}


cv::Mat warpImgWithFlow(cv::Mat img, cv::Mat flow)
{
    Mat flowMap(flow.size(), CV_32FC2);
    for (int y = 0; y < flow.rows; ++y)
    {
        for (int x = 0; x < flow.cols; ++x)
        {
            Point2f f = flow.at<Point2f>(y, x);
            flowMap.at<Point2f>(y, x) = Point2f(x + f.x, y + f.y);
        }
    }

    Mat newFrame;
    remap(img, newFrame, flowMap, Mat(), INTER_LANCZOS4);
    return newFrame;
}


cv::Mat compute_pose_image(const Pose &pose, int height, int width)
{
  cv::Mat_<cv::Vec<uint8_t,3> > rv = cv::Mat_<cv::Vec<uint8_t,3> >::zeros(height,width);
  cv::Mat_<double> axes = pose_axes(pose);
  cv::Mat_<double> scaling = cv::Mat_<double>::eye(3,3);

  for (int i = 0; i < axes.cols; i++) {
    axes(0,i) = -0.5*double(width)*(axes(0,i) - 1);
    axes(1,i) = -0.5*double(height)*(axes(1,i) - 1);
  }

  cv::Point centre(width/2, height/2);
  // pitch
  cv::line(rv, centre, cv::Point(axes(0,0), axes(1,0)), cv::Scalar(255,0,0));
  // yaw
  cv::line(rv, centre, cv::Point(axes(0,1), axes(1,1)), cv::Scalar(0,255,0));
  // roll
  cv::line(rv, centre, cv::Point(axes(0,2), axes(1,2)), cv::Scalar(0,0,255));

  return rv;
}


void findLandmarksFaceSDK(Mat img, vector<Point2d>& shape2d, vector<Point3d>& shape3d,
                          Pose& pose, Rect rect)
{
    string model_pathname = DefaultFaceTrackerModelPathname();
    string params_pathname = DefaultFaceTrackerParamsPathname();

    Ptr<myFaceTracker> ft = dynamic_cast<myFaceTracker*>(LoadFaceTracker());

    //ft->_sinit._fdet = new FakeFaceDet(rect);

    if(ft.empty())
    {
        cout << "Failed to load Face SDK but it was expected" <<endl;
    }
    else
    {
        cout << "It's pretty strange but we've loaded Face SDK" << endl;
    }

    Ptr<FaceTrackerParams> params = LoadFaceTrackerParams();

    Mat gray;
    cvtColor(img, gray, CV_BGR2GRAY);
    int result = ft->NewFrame(gray, params);

    //try to stabilize
    for(int i = 0; i < 2; i++)
    {
        result = ft->Track(gray, params);
    }

    int tracking_threshold = 5;

    if (result >= tracking_threshold)
    {
        shape2d = ft->getShape();
        shape3d = ft->get3DShape();
        pose = ft->getPose();
    }
    else
    {
        shape2d = ft->getShape();
        shape3d = ft->get3DShape();
        pose = ft->getPose();

        cout << "Something's bad with tracking" << endl;
    }
}


Mat alignToLandmarks(Mat img, std::vector<Point2d> landmarks)
{
    Mat buf;
    Rect boundR = boundingRect(landmarks);
    //set boundR.width == .height
    //int centerx = boundR.x + boundR.width/2;
    //boundR.x = centerx-boundR.height/2;
    //boundR.width = boundR.height;
    Mat aligned = img(boundR);

    std::vector<cv::Point2d> ftShape2d;
    std::vector<cv::Point3d> ftShape3d;
    Pose ftPose;
    findLandmarksFaceSDK(img, ftShape2d, ftShape3d, ftPose, boundR);

    int pose_image_height = 100;
    int pose_image_width = 100;
    cv::Mat poseImage = compute_pose_image(ftPose, pose_image_height, pose_image_width);
    imshow("ft pose", poseImage);
    //waitKey(0);

    Vertices model3d;
    cout << "Loading 3D model..." << endl;
    if(!loadObj("data/model3dstm.obj", model3d))
    {
        cout << "Something went wrong: failed to load 3D model" << endl;
    }

    //filter background points
    {
        Vertices filteredModel;
        for(size_t i = 0; i < model3d.size(); i++)
        {
            Point3d p = model3d[i];
            if(p.y < 0)
            {
                filteredModel.push_back(p);
            }
        }
        model3d = filteredModel;
    }

    Vertices ftPoints3d;
    if(!loadObj("data/face_sdk_3d_pts.obj", ftPoints3d))
    {
        cout << "Something went wrong: failed to load FT 3D points" << endl;
    }

    Vertices basePoints3d;
    if(!loadObj("data/zhu_3d_pts.obj", basePoints3d))
    {
        cout << "Something went wrong: failed to load base 3D points" << endl;
    }

    double modelFx = 492.307710365432; //fx==fy
    double modelCx = 160; //cx==cy

    Matx<double, 3, 3> camMat(modelFx,       0, modelCx,
                                    0, modelFx, modelCx,
                                    0,       0,       1);
    Mat distCoeffs, ftRvec, ftTvec;

    if(ftShape2d.size() > 0)
    {
        solvePnP(ftPoints3d, ftShape2d, camMat, distCoeffs, ftRvec, ftTvec);
        vector<Point2d> modelProjected;
        cv::Mat_<double> ftDetRotm;

        Rodrigues(ftRvec, ftDetRotm);
        Pose ftDetPose;
        Rot2Euler(ftDetRotm, ftDetPose.pitch, ftDetPose.yaw, ftDetPose.roll);
        cout << "pitch/yaw/roll: ";
        cout << ftDetPose.pitch << ' ' << ftDetPose.yaw << ' ' << ftDetPose.roll << endl;

        projectPoints(model3d, ftRvec, ftTvec, camMat, distCoeffs, modelProjected);

        //filter points out of frame
        Vertices filtered;
        vector<Point2d> filteredProjected;
        for(size_t i = 0; i < modelProjected.size(); i++)
        {
            Point2d p2 = modelProjected[i];
            if(p2.x >= 0 && p2.y >= 0 && p2.x < img.cols && p2.y < img.rows)
            {
                filtered.push_back(model3d[i]);
                filteredProjected.push_back(p2);
            }
        }\
        model3d = filtered;
        modelProjected = filteredProjected;

        Mat occlBuf(img.size(), CV_8U, Scalar(0));
        const int toAdd = 30;
        for(size_t i = 0; i < modelProjected.size(); i++)
        {
            Point2d p2 = modelProjected[i];
            uchar& val = occlBuf.at<uchar>(p2);
            val = saturate_cast<uchar>(val+toAdd);
        }
        //GaussianBlur(occlBuf, occlBuf, Size(15, 15), 9);
        imshow("ft projected", occlBuf);
    }

    //TODO:choose one of 2 poses

    //TODO:frontalization:
    //TODO:transform model to found pose
    //???TODO: warp model to 3d shape
    //TODO: render pose over the image
    //TODO: grab occlusions image & blur it
    //TODO: somehow reproject
    //TODO: somehow restore from other side



    //TODO:

    Mat ftBuf = img.clone();
    for (size_t i = 0; i < ftShape2d.size(); i++)
    {
        cv::circle(ftBuf, ftShape2d[i], 2, Scalar(0, 0, 255), 1, 8, 0);
    }
    imshow("ft landmarks", ftBuf);

    buf = drawPtsOnImg(img, landmarks);
    imshow("base landmarks", buf);
    waitKey(0);

    return aligned;
}

