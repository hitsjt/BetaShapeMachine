This folder contains information related to the use of our deep generative model for fine-grained classification per shape family. 

a) classification_data.txt: ground-truth labels for each shape in the BHCP dataset. The label 'other' means that the shape seems rather unique in the dataset and cannot be easily classified into a standard fine-grained category. The shapes labeled as 'other' do not participate in training and testing. 

b) descriptor.txt: we provide descriptor values produced by performing mean-field inference in our generative model given each input shape listed in 'classification_data.txt' (in the same order). The activation probabilities of the uppermost layer nodes are used as descriptors.  

c) split.txt: we provide the training and test split for evaluation. For each shape listed in 'classification_data.txt' (in the same order), we have a single bit. When it is one, the corresponding shape is used for training. When it is zero, it is used for testing.

d) classification (sub-folder): we show the classification results for each fine-grained category. 

The classification accuracy is evaluated on the shapes of the *test split* by using nearest neighbor classification based on L1 norm distances of the descriptors produced in the uppermost layer of our generative model. 