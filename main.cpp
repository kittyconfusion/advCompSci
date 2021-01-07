
//
//  main.cpp
//  LLTemplate
//
//  Created by James Shockey on 12/6/16.
//  Copyright © 2016 James Shockey. All rights reserved.
//


/*
 *
 *	Linked List lab.
 *	- Build a library for singly linked list.
 *	- Replace the airport array in main with a Linked List.
 *  - sort the array. 
 *	
 */


#include <iostream>
#include <fstream>
#include <cmath> 
#include <stdio.h>
#include "slist.h"
#include <string.h>

using namespace std;

class Airport
{
public:
    char    code[5];
    double   longitude;
    double   latitude;
    
};



void simpleSortTotal(Airport* s[], int c);
double distanceEarth(double lat1d, double lon1d, double lat2d, double lon2d);
void printAirport(Airport* a, bool endLine = true);
double kil2mil(double kilos);
void simpleSortTotal(sList* airportArr, double AustinLat, double AustinLong);
double distanceFromAUS(Airport* a, double AustinLat, double AustinLong);
void quicksort(sList* airports, int startIndex, int endIndex, double AustinLat, double AustinLong);
int partition(sList* airports, int startIndex, int endIndex, double AustinLat, double AustinLong);

int main()
{
    ifstream infile;
    int i=0;
    char cNum[10] ;
    sList *airportArr = new sList();			// Replace array with Linked List
    int   airportCount;
    //Airport* a[13500];
    
    infile.open ("./USAirportCodes.csv", ifstream::in);
    if (infile.is_open())
    {
        int   c=-1;
        
        char t[256];
        infile.getline(t, 256,'\n'); //Skip the first line
        
        while (infile.good())
        {
            Airport *tempAirport = new Airport();
            
            infile.getline(tempAirport->code, 256, ',');
            infile.getline(cNum, 256, ',');
            tempAirport->latitude = atof(cNum);
            infile.getline(cNum, 256, '\n');
            tempAirport->longitude = atof(cNum);
            
            airportArr->add(tempAirport);
            
            if (!(c % 1000)) {
                //cout << airportArr->size() << " " << c << endl;
                printAirport((Airport*)(airportArr->get(c)));
            }

            /*
            if (!(c % 1000))
            {
                cout << airportArr[c]->code << " long: " << airportArr[c]->longitude << " lat: " << airportArr[c]->latitude <<  endl;
                cout << airportArr[c+1]->code << endl; //" long: " << airportArr[c+1]->longitude << " lat: " << airportArr[c+1]->latitude <<  endl;                               
            }
            */

            
            i++ ;
            c++;
        }
        
        cout << endl;
        
        //SORTING THE ARRAY
        
        //Find coords of Austin airport and store them for future reference.
        double AustinLong = 0;
        double AustinLat = 0;
        
        for(int i = 0; i < airportArr->size() - 1; i++) {
          if(strncmp(((Airport*)(airportArr->get(i)))->code,"AUS", 4) == 0) {
            AustinLong = ((Airport*)(airportArr->get(i)))->longitude;
            AustinLat = ((Airport*)(airportArr->get(i)))->latitude;
          }
        }
  
        cout << "Austin coords found at lat: " << AustinLat << " long: " << AustinLong << ".\n" << endl;

        simpleSortTotal(airportArr, AustinLat, AustinLong);
        cout << "Done sorting.\n\n";
          
        //Because airports are already sorted by distance no need to check any more airports 
        //after the first one is found farther than 100 miles away.
        
        cout << "Airports within 100 miles of AUS." << endl;
        bool over100Miles = false;
        for(int i = 0; i < airportArr->size() - 1; i++) {
          if(!over100Miles) {
            double currentDistance = kil2mil(distanceFromAUS((Airport*)(airportArr->get(i)), AustinLat, AustinLong));
            
            if(currentDistance <= 100) {
              cout << ((Airport*)(airportArr->get(i)))->code << " is " << currentDistance << " miles away from AUS." << endl;
            }
            else {
              over100Miles = true;
            }
          }
        }
        
        //Find farthest airport from AUS.
        Airport* farthestAirport = (Airport*)(airportArr->get(airportArr->size() - 2));
        cout << "\nFarthest airport from AUS is " << farthestAirport->code << " at " << kil2mil(distanceFromAUS(farthestAirport, AustinLat, AustinLong)) << " miles away.";
        
        
        airportCount = c;
        infile.close();
        /*
         for (int c=0; c < airportCount; c++)
            if (!(c % 1000))
            {
                cout << airportArr[c]->code << " long: " << airportArr[c]->longitude << " lat: " << airportArr[c]->latitude <<  endl;
                cout << airportArr[c+1]->code << " long: " << airportArr[c+1]->longitude << " lat: " << airportArr[c+1]->latitude <<  endl;
                cout <<"Distance between " << airportArr[c]->code << " and " << airportArr[c+1]->code << " is "
                  << distanceEarth( airportArr[c]->longitude, airportArr[c]->latitude , airportArr[c+1]->longitude, airportArr[c+1]->latitude) << endl;
            }
        */


    }
    else
    {
        cout << "Error opening file";
    }
    
}

void printAirport(Airport* a, bool endLine) {
  cout << a->code << " lat: " << a->latitude << " long: " << a->longitude;
  if(endLine) {
    cout << "\n";
  }
}

#define pi 3.14159265358979323846
#define earthRadiusKm 6371.0

// This function converts decimal degrees to radians
double deg2rad(double deg) {
  return (deg * pi / 180);
}

//  This function converts radians to decimal degrees
double rad2deg(double rad) {
  return (rad * 180 / pi);
}


/**
 * Returns the distance between two points on the Earth.
 * Direct translation from http://en.wikipedia.org/wiki/Haversine_formula
 * @param lat1d Latitude of the first point in degrees
 * @param lon1d Longitude of the first point in degrees
 * @param lat2d Latitude of the second point in degrees
 * @param lon2d Longitude of the second point in degrees
 * @return The distance between the two points in kilometers
 */
double distanceEarth(double lat1d, double lon1d, double lat2d, double lon2d) {
  double lat1r, lon1r, lat2r, lon2r, u, v;
  lat1r = deg2rad(lat1d);
  lon1r = deg2rad(lon1d);
  lat2r = deg2rad(lat2d);
  lon2r = deg2rad(lon2d);
  u = sin((lat2r - lat1r)/2);
  v = sin((lon2r - lon1r)/2);
  return 2.0 * earthRadiusKm * asin(sqrt(u * u + cos(lat1r) * cos(lat2r) * v * v));
}

// This function converts kilometers to miles
double kil2mil(double kilos) {
  return kilos * 0.621371;
}

double distanceFromAUS(Airport* a, double AustinLat, double AustinLong) {
  return distanceEarth(a->latitude, a->longitude, AustinLat, AustinLong);
      
}

//Provide sort routine on linked list
//Pseudocode originally taken from https://en.wikipedia.org/wiki/Quicksort under Hoare partition scheme.

void quicksort(sList* airports, int startIndex, int endIndex, double AustinLat, double AustinLong) {
  if (startIndex < endIndex) { 
    int p = partition(airports, startIndex, endIndex, AustinLat, AustinLong);
    quicksort(airports, startIndex, p, AustinLat, AustinLong);
    quicksort(airports, p + 1, endIndex, AustinLat, AustinLong);
  }
  else if(!(startIndex % 1000)) {
    cout << "Sorted through " << startIndex + 1 << " airports out of " << airports->size() << "." << endl;
  }
}

int partition(sList* airports, int startIndex, int endIndex, double AustinLat, double AustinLong) {
  double pivot = distanceFromAUS((Airport*)(airports->get((startIndex + endIndex) / 2)), AustinLat, AustinLong);
      
  int i = startIndex - 1;
  int j = endIndex + 1;
  
  while(true) {
    do {
        i++;
    } while(distanceFromAUS((Airport*)(airports->get(i)), AustinLat, AustinLong) < pivot);
    do {
        j--;
    } while(distanceFromAUS((Airport*)(airports->get(j)), AustinLat, AustinLong) > pivot);
    
    if(i >= j) { 
      return j;
    }
    airports->swap(i, j);
  }
}


void simpleSortTotal(sList* airportArr, double AustinLat, double AustinLong) {

  quicksort(airportArr, 0, airportArr->size() - 2, AustinLat, AustinLong);
  
}
  //Unused code
  /*
  for(int i = 0; i < airportArr->size() - 1; i++) {
    double minValue = 24901.0000;
    int minValueIndex;
    for(int c = i; c < airportArr->size() - 1; c++) {
      double distanceBetween = distanceEarth(((Airport*)(airportArr->get(c)))->latitude, ((Airport*)(airportArr->get(c)))->longitude, AustinLat, AustinLong);
      
      if(distanceBetween < minValue) {
        minValue = distanceBetween;
        minValueIndex = c;
      }
    }
  
    //Progress Reporter
    if(!(i % 1)) {
      cout << "Sorted through " << i + 1 << " airports out of " << airportArr->size() << "." << endl;
    }
    airportArr->swap(i, minValueIndex);
  }
  */





        //Code for testing functionality of sList
        /*sList *airportArr2 = airportArr->subList(0,10);
        
        for(int j = 0; j < 15; j++) {
          printAirport((Airport*)(airportArr2->get(j)),false);
          cout << " " << j << endl;
        }*/
        
        /* //Multipurpose testing code
        for(int j = 0; j < 10; j++) {
          printAirport((Airport*)(airportArr->get(j)),false);
          cout << " " << j << endl;
        }
        
        cout << endl;
        airportArr->swap(3,3);
        
        for(int j = 0; j < 10; j++) {
          printAirport((Airport*)(airportArr->get(j)),false);
          cout << " " << j << endl;
        }
        */