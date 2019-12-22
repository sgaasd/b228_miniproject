#include <ros/ros.h>
#include <kobuki_msgs/CliffEvent.h>
#include <kobuki_msgs/BumperEvent.h>
#include "std_msgs/String.h"
using namespace std;

/*Publisher varible is initialised*/
ros::Publisher miniproject_pub;

/*A class called Safety_CallBack, that contains the different functions, 
is created*/
class Safety_CallBack {
    public: 
        /*The function for the Cliff sensor is created. 
        With poniter that passes data from each sensor and its state*/
    void CliffCallback(const kobuki_msgs::CliffEvent::ConstPtr& msg){
        bool cliffs = msg->state;
        int sensors = msg->sensor;


    }
    /*The function BumperCallBack tells if the bumper is pressed 
    and which side is pressed*/
    void BumperCallback(const kobuki_msgs::BumperEvent::ConstPtr& msg){
        bool hit = msg->state;
        int bump = msg->bumper;


    }
        
    private:
};

int main(int argc, char *argv[]){

    /*Initelizing ros*/
    ros::init(argc, argv, "Safety");
    ros::NodeHandle n;
    
    /*To call the class it needs to be declared*/
    Safety_CallBack safetyClass;
    
    /*Subcribing to "/mobile_base/events/cliff".
    Evertime an advertisment is made on the 
    topic "/mobile_base/events/cliff" run "CliffCallBack"*/
    ros::Subscriber Cliff_sub = n.subscribe("/mobile_base/events/cliff",
     1, &Safety_CallBack::CliffCallback, &safetyClass);
    
    /*Subcribing to "mobile_base/events/bumper". 
    Evertime an advertisment is made on the 
    topic "mobile_base/events/bumper" run "BumperCallBack" */
    ros::Subscriber Bumper_sub = n.subscribe("mobile_base/events/bumper",
     1, &Safety_CallBack::BumperCallback, &safetyClass);

     ros::Publisher miniproject_pub = n.advertise<std_msgs::String>("miniproject", 1);

    /*The program has run continuously */
    ros::spin();

    return 0;
}