        // *** Author: Group B228    *** //
        // *** Project: Mini project *** //
        // *** Node: Safety node     *** //
        // *** Created: 31-12-2019   *** //

#include <ros/ros.h>
#include <kobuki_msgs/CliffEvent.h>
#include <kobuki_msgs/BumperEvent.h>
#include <b228_miniproject/safety_msg.h>

using namespace std;

/*A publisher is declared*/
ros::Publisher miniproject_pub;

/*A class for the safety methods is initialized*/
class Safety_CallBack {
    public: 
    
    /*The CliffCallback method is initialized*/
    void CliffCallback(const kobuki_msgs::CliffEvent::ConstPtr& msg){
        /*Variables are assigned the values inside msg*/
        bool cliffs = msg->state;
        int sensors = msg->sensor;
        /*A variable for publishing is declared*/
        b228_miniproject::safety_msg safety_msg;
        /* If the sensor was activated, publish what side was activated */
        if (cliffs == 1) {
            safety_msg.side = sensors;
            miniproject_pub.publish(safety_msg);
        }
    }
    
    /*The PumperCallback method is initialized*/
    void BumperCallback(const kobuki_msgs::BumperEvent::ConstPtr& msg){
        /*Variables are assigned the values inside msg*/
        bool hit = msg->state;
        int bump = msg->bumper;
        /*A variable for publishing is declared*/
        b228_miniproject::safety_msg safety_msg;
        /* If the sensor was activated, publish what side was activated */
        if (hit == 1) {
            safety_msg.side = bump;
            miniproject_pub.publish(safety_msg);
        }
    }
        
    private:
};

int main(int argc, char *argv[]){

    /*The ROS node is initialized, and a nodehandle is declared*/
    ros::init(argc, argv, "Safety");
    ros::NodeHandle n;
    
    /*A varibale to pass to the functions that is called in the subsriber is decalred*/
    Safety_CallBack safetyClass;

    /*The subsribers are assiged*/
    ros::Subscriber Cliff_sub = n.subscribe("/mobile_base/events/cliff",
     1, &Safety_CallBack::CliffCallback, &safetyClass);   
    ros::Subscriber Bumper_sub = n.subscribe("/mobile_base/events/bumper",
     1, &Safety_CallBack::BumperCallback, &safetyClass);

    /*The publisher is assigned*/
    ros::Publisher miniproject_pub = n.advertise<b228_miniproject::safety_msg>("/miniproject/safety", 1);

    ros::spin();

    return 0;
}