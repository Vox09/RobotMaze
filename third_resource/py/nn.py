#!/usr/bin/python3
import numpy as np

class Perception:
    def __init__(self, weights = np.array([100]), threshold = 0):
        self.weights = weights
        self.threshold = threshold

    def activate(self,inputs):
        strenth = np.dot(inputs, self.weights)
        if strenth >= self.threshold:
            result = 1
        else:
            result = 0
        return result

class Network:
    def __init__(self):
        self.p11=Perception(100,50)
        self.p12=Perception(100,100)
        self.p21=Perception([100,-100],100)
    
    def run(self,in_sensor):
            p11_result = self.p11.activate(in_sensor)
            p12_result = self.p12.activate(in_sensor)
            p21_result = self.p21.activate([p11_result,p12_result])
            return [p12_result,p21_result] 


