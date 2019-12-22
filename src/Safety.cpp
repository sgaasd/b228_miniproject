#include <ros/ros.h>
#include <kobuki_msgs/CliffEvent.h>
#include <kobuki_msgs/BumperEvent.h>
#include "std_msgs/String.h"
using namespace std;

ros::Publisher miniproject_pub;


class Safety_CallBack {
    public: 
        
    void CliffCallback(const kobuki_msgs::CliffEvent::ConstPtr& msg){
        bool cliffs = msg->state;
        int sensors = msg->sensor;
        /* Her skal indsættes noget med bumper til den der publisher */
        miniproject_pub = sensors;

    }
    
    void BumperCallback(const kobuki_msgs::BumperEvent::ConstPtr& msg){
        bool hit = msg->state;
        int bump = msg->bumper;
        /* Her skal indsættes noget med bumper til den der publisher */
        miniproject_pub = bump;

    }
        
    private:
};

int main(int argc, char *argv[]){

    ros::init(argc, argv, "Safety");
    ros::NodeHandle n;
    
    
    Safety_CallBack safetyClass;
    

    ros::Subscriber Cliff_sub = n.subscribe("/mobile_base/events/cliff",
     1, &Safety_CallBack::CliffCallback, &safetyClass);
    
    
    ros::Subscriber Bumper_sub = n.subscribe("mobile_base/events/bumper",
     1, &Safety_CallBack::BumperCallback, &safetyClass);

    ros::Publisher miniproject_pub = n.advertise<std_msgs::String>("miniproject", 1);

    
    ros::spin();

    return 0;
}