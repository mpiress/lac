Lazy Associative Classification - LAC

Associative classification refers to a class of algorithms that is very eficient in classification problems. Data in such domain are multidimensional, with data instances represented as points of a fixed-length attribute space, and are exploited from two large sets: training and testing datasets. Models, known as classifiers, are mined in the training set by class association rules and are used in eager and lazy strategies for labeling test data instances.

LAC is a demand-driven associative classification that uses local searches in D to compose classifiers, whenever an unlabeled data instance t in T is provided. Therefore, it is assumed that pairs in D are in some sense related to pairs in T, sampled independently and identically by the same distribution P(t|p). Facts that make LAC capable to afford a better global approximation of the target function F by local models, which leads to greater accuracy than noticed in traditional classification models.

In this project, an extension of the original LAC is introduced and It can be used as a Python library imported. For that, after compiling using MakeFile, you can use the built lac.so in their Python projects. 

