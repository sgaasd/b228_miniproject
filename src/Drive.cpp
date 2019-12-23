#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <b228_miniproject/safety_msg.h>

/*A prototype of the Drive function is made*/
void drive(const b228_miniproject::safety_msg::ConstPtr& msg);

/*Variables for counting, and the safety functions is declared and initialized*/
int PreCount = 0;
int Count = 0;
int Safety = 0;

/*A ros publisher is declared*/
ros::Publisher cmd_vel_pub;

/*A function for returning Geometry_msgs::Twist variables is made
    This function helps shorten the overall code.*/
geometry_msgs::Twist DriveMsg(float x, float z){
    geometry_msgs::Twist cmd_vel_message;
    cmd_vel_message.angular.z = z;
    cmd_vel_message.linear.x = x;
    return cmd_vel_message;
}

/*A function for calling when a safety action should be executet is declared.*/
void safetyAction(int SideHit){
    ros::Rate loop_rate(20);
    switch (SideHit)
        {
            /*If a sensor on the left side is activated the robot 
            will first drive backwards and turn right*/
            case 0:
            for(int i=0; i<=30; i++){ 
                cmd_vel_pub.publish(DriveMsg(-0.2, 0.0));
                loop_rate.sleep();
            }
            for(int i=0; i<=30; i++){ 
                cmd_vel_pub.publish(DriveMsg(0.0, -(0.75)));
                loop_rate.sleep();
            }
            break;
            /*If a sensor on the middle is activated the robot 
            will drive backwards and turn left*/
            case 1:
            for(int i=0; i<=30; i++){ 
                cmd_vel_pub.publish(DriveMsg(-0.2, 0.0));
                loop_rate.sleep();
            }
            for(int i=0; i<=30; i++){
                cmd_vel_pub.publish(DriveMsg(0.0, (0.75)));
                loop_rate.sleep();
            }
            break;
            /*If a sensor on the right side is activated the robot 
            will drive backwards and turn left*/
                case 2:
            for(int i=0; i<=30; i++){ 
                cmd_vel_pub.publish(DriveMsg(-0.2, 0.0));
                loop_rate.sleep();
            }
            for(int i=0; i<=30; i++){
                cmd_vel_pub.publish(DriveMsg(0.0, (0.75)));
                loop_rate.sleep();
            }
            break;
        }
}

int main(int argc, char *argv[])
{
    /*The ROS node is initialized, and a nodehandle is declared*/
    ros::init(argc, argv, "Drive");
    ros::NodeHandle n;

    /*A ROS subscriber, and the publisher is assigned.*/
    ros::Subscriber miniproject_sub = n.subscribe("/miniproject/safety", 1, drive);
    cmd_vel_pub = n.advertise<geometry_msgs::Twist>("/cmd_vel_mux/input/teleop", 1);
    
    /*As long as ROS*/
    while (ros::ok)
    {
        geometry_msgs::Twist cmd_vel_message;
        if (PreCount != Count)
        {
            /*Hvis drive funktionen har kørt: Kør safetyAction funktionen, med den side der er ramt som parameter*/
            safetyAction(Safety);
            PreCount = Count;
        } else {
            /*Hvis ikke, så kør ligeud*/
            cmd_vel_pub.publish(DriveMsg(0.0, 0.2));
        }
        ros::spinOnce();
    }  
    ros::spin();
    return 0;
}


void drive(const b228_miniproject::safety_msg::ConstPtr& msg){
    //std::cout << "drive funktion aktiveret" << std::endl;
    Safety = msg->side;
    Count++;
}