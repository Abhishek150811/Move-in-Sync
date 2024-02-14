#include <bits/stdc++.h>
using namespace std;


class Database ; 
class Passenger ; 
class Trip ; 
class Admin ; 
class Driver ; 
class Passenger_Companion ; 
// I have been give the task of creating Ride sharing Platform
// I am creating a HLD of Ride hsaring platform

class Passenger
{

protected:
    // Name of the passenger
    string full_name;

    // Unique id of the passenger
    // we can change the data type to big int in case of other languages to accomodata the increaing
    // user base
    long long passenger_id;

    // phone number of the passenger
    string passenger_phone_num;

    // This will be pickup point which is choosen by that passenger
    string passenger_pickup_point;

    // This will be the drop location which is choosen by that passenger
    string passenger_drop_point;

    // This will be at what time he need to picked up
    string passenger_pickup_time;
    // This will be the current geo location of that passenger
    // This first value is lattitude value and the second is longitude value
    pair<double, double> passenger_curr_location = {45, 82};

    // one bool variable to incidate whether the trip is complete or not 
    // by default this will be false and trun to true when it s is complete
    bool has_trip_started = false ; 
    bool is_trip_complete = false ; 

    // This is the last passenger id we will keep on incrementing each time new passenger comes in
    

public:
    // This is the constructor whenever a new passenger will sign up for
    // We are also using some default values for pick up point and drop point in case passenger at that
    // moment does not want to book a ride he just simply wants to sign up for
    // We are also giving a default passenger location because sometimes users don't give access to
    // location so in that case we are setting the default latitude and longitude of that user's
    // country's capital
    Passenger(string name, long long id, string phone_num, string pickup_point = "", string drop_point = "",
              pair<int, int> curr_location = {31, 75})
    {
        full_name = name;
        passenger_id = id;
        passenger_phone_num = phone_num;
        passenger_pickup_point = pickup_point;
        passenger_drop_point = drop_point;
        passenger_curr_location = curr_location;
        
        
    }
    
    long long get_passenger_id(){
        return passenger_id ; 
    }

    string getname(){
        return full_name ; 
    }
    string getpickupanddrop(){
        return passenger_pickup_point + " " + passenger_drop_point ; 
    }
    void printalldetails()
    {
        cout << "Your Full name is : " << full_name << endl;
        cout << "Your Phone number is : " << passenger_id << endl;
        cout << "Your pickup point and drop point is : " << passenger_pickup_point << " " << passenger_drop_point << endl;
        cout << "At what time you need your cab " << passenger_pickup_time << endl;
        cout << "Your current location is : " << passenger_curr_location.first << " N " << passenger_curr_location.second << " E " << endl;
    }

    // for sending the information of trip on whatsapp or smsonly if trip is in progress
    void details_of_trip_on_whatsapp_sms(){
        if(has_trip_started == true && is_trip_complete == false){
            // Then api call will be made on whatsapp server and sms server and it will send the information
            // to the passenger mobile number
        }
        else{
            cout << "Your trip is completed and you have no active journey right now" << endl;
        }
    }

    // To get all the trips that passenger has done
    // void get_all_trips_of_passengers(){
    //     Database::get_all_trips_by_passenger_id(passenger_id) ; 
    // }
};

// As this will inherit all the properties of its parent class
// so it will have location and drop point of passenger
class Passenger_Companion : protected Passenger{
    public: 
    // This method will be used to check the current status fo the trip whether is currently undergoing
    // or whether it is finished
    void check_trip_status(){
        if( has_trip_started == true &&  is_trip_complete == true){
            cout << "Traveller has safely reached there destination" << endl;
        }
        else{
            cout <<"No the Traveller is currently travelling" << endl;
        }
    } 

    // This function will be used for sending notification to your phone 
    void send_notification(){

    }

    void tell_is_nearby(pair<double,double> &companion_curr_location){

        // This will calculate the passenger's locatin with his companion's location 
        double distance = sqrt(pow(companion_curr_location.first - passenger_curr_location.first , 2) + 
                                pow(companion_curr_location.second + passenger_curr_location.second , 2)) ;

        // Then based on a certain value we will calculate whether is is near or not                     
        if(distance < 20){
            cout << "Yes the Passenger is near to you" << endl;
        }
        else{
            cout << "No the passenger is not near to you" << endl;
        }
    }

    // This will be used to send the feedback the passengers' companion for that ride
    // void send_feedback( string new_feedback){
    //     Database::push_feedback(passenger_id , new_feedback ) ; 
    //     cout << "Thank you for your kind words" << endl;
    // }
};

class Driver
{

protected:
    // Name of the Driver
    string driver_name;

    // Unique id of the driver
    // we can change the data type to big int in case of other languages to accomodata the increaing
    // drivers
    long long driver_id;

    // Phone number of the driver
    string driver_phone_num;

    // Cab number phate
    string cab_number_plate;

    // Car type egs: mini , sedan xl
    string car_type;

public:
    Driver(string name, long long id, string phone_num, string cab_num, string type)
    {
        driver_name = name;
        driver_id = id;
        driver_phone_num = phone_num;
        cab_number_plate = cab_num;
        car_type = type;
    }
    long long get_driver_id() {
        return driver_id ; 
    }
    string get_driver_name(){
        return driver_name ; 
    }
    string get_driver_phone_num(){
        return driver_phone_num ; 
    }
    string get_cab_number_plate(){
        return cab_number_plate  ;
    }
    string get_car_type(){
        return car_type ; 
    }

    void printalldetails()
    {
        cout << "Name of driver is : " << driver_name << endl;
        cout << "Driver's phone number is : " << driver_phone_num << endl;
        cout << "Driver's car's number plate is : " << cab_number_plate << endl;
        cout << "Driver's car type is : " << car_type << endl;
    }
};

class Trip
{
protected:
    // Every trip will be having a unique id
    long long trip_id;

    // The driver name will be ininitialised from driver class
    string driver_name;

    // The driver phone number  will be initialised from the driver class
    string driver_phone_num;

    // Cab number will be initialised from the driver class
    string cab_number;

    // This will be a vector of total number of passengers travelling together
    // Becasue they can vary in side so that is why we wil use a vector
    vector<Passenger *> total_passengers;

    // Total pick up points  of different passengers
    string car_type;

public:
    Trip(long long id , string d_name , string d_phone_num , string cab_num , string c_type){
        trip_id = id ;
        driver_name = d_name ; 
        driver_phone_num = d_phone_num ; 
        cab_number = cab_num ; 
        car_type = c_type ; 
    }

    long long  get_trip_id(){
        return trip_id ; 
    } 
    // This function will print all the details of trip including the driver name , his phone number
    // his cab number and cab type and also the list of all the fellow passengers with there 
    // respective pickup location and drop location
    void printalldetails()
    {
        cout << "Driver name is : " << driver_name << endl;
        cout << "Driver phone number is : " << driver_phone_num << endl;
        cout << "Cab number is : " << cab_number << endl;
        for(int i = 0 ; i < total_passengers.size()  ;i++){
            cout << "Passenger " << i + 1 << "  " << total_passengers[i]->getname() << endl;
            cout << "Your pickup and drop location is : " << total_passengers[i]->getpickupanddrop() << endl;
        }
        
    }
    void add_Passengers(Passenger * obj){
        total_passengers.push_back(obj) ; 
    }
};
class Database
{
    // Declaring inside protected class because we also want to give access to the derived classses
    // Protected will the best access modifier because no one can directly access them outside the
    // class and we can also pass these vairable to other calsses who all need them
protected:
    // I am using map because it will give me faster access to data in logn time
    //  passengerid , passenger obj
    static map<long long, Passenger *> passengers;

    // Trip id , Trip objects
    static map<long long, Trip *> trips;

    // Driver id , Driver objects
    static map<long long, Driver *> drivers;

    // key will be passenger id and string will be its feedback given my passenger companion
    static map<long long , string> feedback ;

    static map<long long , vector<long long> > passenger_to_trip ; 

public:
    // This function is used for pushing feedback into the database

    // This function is used for getting 
    static void get_all_trips_by_passenger_id(long long passenger_id){
        
        for(auto &iter : passenger_to_trip[passenger_id]){
            cout << iter << endl;
        }
    }

    // All the function below are to push the new details into there corresoponding data bases
    static void push_feedback(long long id , string new_feedback){
        feedback[id] = new_feedback ; 
    }
    static void push_passenger_details(long long id , Passenger * obj) {
        passengers[id] = obj ; 
    }
    static void push_trip_details(long long id , Trip * obj){
        trips[id] = obj ; 
    }

    static void push_driver_details(long long id , Driver * obj){
        drivers[id] = obj ; 
    }
    
};
class Admin : public Database
{
public:
    Admin() : Database(){

    }
    // This function is for accessing all the information regarding all the passengers that have
    // used this app
    void printallusers()
    {

        for (auto &iter : passengers)
        {
            // We got the passenger id as a key from the map
            long long pid = iter.first;

            // we got the passenger data by accessing the public function of passenger class
            iter.second->printalldetails();
        }
    }

    // To get all the trip details
    void printalltrips()
    {
        for (auto &iter : trips)
        {
            // We will get the trip id as a key from the map
            long long tid = iter.first;

            // 
            iter.second->printalldetails();
        }
    }

    // To get all the drivere and there details
    void printalldriver()
    {
        for (auto &iter : drivers)
        {
            // We got the driver id
            long long id = iter.first;

            // Now we will access all the data of the driver using public function of driver class
            iter.second->printalldetails();
        }
    }

    // To get all the user experience feedback 
    void printallfeedback(){
        for(auto &iter : feedback){
            cout << iter.second << endl; 
        }
    }
};




int main()
{
    // Creating 2 new passengers
    Passenger * p1 = new Passenger("Abhishek Mishra" , 12115047 , "7027774921" , "Jalandhar" , "delhi" );
    Passenger * p2 = new Passenger("Mohit" , 12115750 , "1234567890" , "ambala" , "Delhi" ) ; 

    Driver * d1 = new Driver("Mukesh" , 1325698 , "9876543210" , "HR 01 8051" , "sedan") ; 
    // Creating 2 new Trips
    Trip * t1 = new Trip(101 , d1->get_driver_name() ,d1->get_driver_phone_num()  , d1->get_cab_number_plate() , d1->get_car_type()) ; 

    // pushing the data into the shared ride into the same trip
    cout << endl << "***************************************************************************************** "; 
    cout << endl;
    t1->add_Passengers(p1) ;
    t1->add_Passengers(p2) ; 

    cout << "Printing individual passengeres details" << endl;
    p1->printalldetails() ; 
    cout << endl;
    p1->printalldetails() ; 

    
    cout << endl << endl;
    cout << "****************************************************************************" << endl;
    cout << "Printing entire trips common passengers" << endl;
    t1->printalldetails() ; 
    
    return 0;
}
