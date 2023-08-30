
#include <iostream>
#include <type_traits>
#include <string>

struct Node{
    int data;
    Node* left;
    Node* right;

};



struct FinderStruct {
    Node* preptr;
    Node* structptr;
    bool flag;
};


struct CombinedStructs {
    Node* struct1ptr;
    Node* struct2ptr;
};

void add(Node* current, int new_data, bool brand_new= true){
// fix first node


    if ((brand_new==true) and (current->left == NULL) and (current->right == NULL)){
        current -> data= new_data;

        return;
    }

    else {
        if (new_data == (current->data)){
                std:: cout<<"Element "<<new_data<<"is already present."<<std::endl;
                return;
            };
        Node* new_node = new Node();
        new_node -> data= new_data;

        if ((current->left != NULL) and (current->right != NULL)){
            if (new_data < (current->data)){
                add(current-> left,new_data, false);
            }
            else if (new_data > (current->data)){
                add(current-> right,new_data, false);
            };
        }
        
        else if (new_data < (current->data)){
            if (current->left != NULL){
                add(current->left, new_data, false);
            }
            else{
                current->left= new_node;
                return;
            };
        }
        else if (new_data > (current->data)){
            if (current->right != NULL){
                add(current->right, new_data, false);
            }
            else{
                current->right= new_node;
                return;
            };
        };
        

        
    }


};

void sort(Node* current){
    
    if (current->left != NULL){
        sort(current->left);
        std::cout << current->data<<std::endl;
    }
    else{
        std::cout << current->data<<std::endl;
    }
    
    if (current->right != NULL){
        sort(current->right);
    }
    
    if ((current->left == NULL) and (current->right == NULL)){
        return;
    };
    
    return;
};

// what if target is not present??????

FinderStruct finder(Node* current, int target, Node* pre, Node* out, bool flag, const std::string& mode){
    if (flag==true){
        FinderStruct result; 
        result.flag= flag;
        result.preptr= pre;
        result.structptr = out;
        return result;
    }
    if (mode== "target"){
        if (current->data==target){
            flag= true;
            out = current;
            FinderStruct result; 
            result.preptr= pre;
            result.flag= flag;
            result.structptr = out;
            return result;}
        
        if ((current->left)!=NULL){
            if ((current->left)->data==target){
                FinderStruct res;
                pre= current;// case where the target is the head?
                res= finder(current->left, target, pre, out, flag, mode);
                flag= res.flag;
                out= res.structptr;
            }
           
        
        }
        
        if ((current->right)!=NULL) {
            if ((current->right)->data==target){
                FinderStruct res;
                pre= current;
                res= finder(current->right, target, pre, out, flag, mode);
                flag= res.flag;
                out= res.structptr;
            }
            
        
        }
        
        if ((target< current->data)&((current->left)!=NULL)){
            FinderStruct res;
            res= finder(current->left, target, pre, out, flag, mode);
            pre= res.preptr;
            flag= res.flag;
            out= res.structptr;
        }
        else if ((target> current->data)& ((current->right)!=NULL)){
            FinderStruct res;
            res= finder(current->right, target, pre, out, flag, mode);
            pre= res.preptr;
            flag= res.flag;
            out= res.structptr;
        }
        else if (current->left!=NULL){
            FinderStruct res;
            res= finder(current->left, target, pre, out, flag, mode);
            pre= res.preptr;
            flag= res.flag;
            out= res.structptr;
        }
        else if (current->right!=NULL){
            FinderStruct res;
            res= finder(current->right, target, pre, out, flag, mode);
            pre= res.preptr;
            flag= res.flag;
            out= res.structptr;
        }
         //CAN DO THIS??
        FinderStruct result; //CAN DO THIS??
        result.flag= flag;
        result.preptr=pre;
        result.structptr = out;
        return result;

    }
    else if (mode=="replacement"){
        if (((current->right)->right)==NULL){
            FinderStruct result; //CAN DO THIS??
            result.flag= flag;
            result.preptr= current;
            result.structptr = out;
        }
        if (current->right==NULL){
            flag= true;
            out = current;
            FinderStruct result; //CAN DO THIS??
            result.flag= flag;
            result.preptr= pre;
            result.structptr = out;
            return result;
        }
        else {
            FinderStruct res;
            res= finder(current->right, target, pre, out, flag, mode);
            flag= res.flag;
            pre= res.preptr;
            out= res.structptr;
        }

    }

    FinderStruct result; //CAN DO THIS??
    result.flag= flag;
    result.preptr= pre;
    result.structptr = out;
    return result;
    }

void deletion(Node* head, int target){
    FinderStruct output;
    output=finder(head, target, NULL, NULL, false, "target");
    Node* targetptr = output.structptr;
    Node* preptr= output.preptr;
    FinderStruct replacement;
    Node* resptr= NULL; 
    Node* reppre= NULL;


    if ((targetptr->left != NULL) and (targetptr->right != NULL)){
        replacement=finder(targetptr->left, target, NULL, NULL, false, "replacement");
        resptr= replacement.structptr;
        reppre= replacement.preptr;
        //std::cout<<resptr->data;
        replacement.preptr = NULL;
        replacement.structptr = NULL;
        reppre->right= resptr->left;
        
    }
    else if ((targetptr->left != NULL)){
        resptr= targetptr->left;
    }
    else if ((targetptr->right != NULL)){
        resptr= targetptr->right;
    }

    if(preptr==NULL){//when root node is target
        if (targetptr->left==resptr){
            targetptr->data= resptr->data;
            targetptr->left= resptr->left;
            delete resptr;
            resptr= NULL;
        }
        else{
            targetptr->data= resptr->data;
            delete resptr;
            resptr= NULL;

        }
    }



    if (resptr != NULL){ //the target is not leaf
        if (output.preptr!= NULL){// the target is not head
            if ((targetptr->data) < ((output.preptr)->data)){
                (output.preptr)->left= resptr;
        
        }
            else if ((targetptr->data) > ((output.preptr)->data)){
                (output.preptr)->right= resptr;
            
        }
        }
       
        if ((targetptr->left != NULL) and (resptr->left ==NULL)){
            if (resptr!= targetptr->left){
            resptr-> left= targetptr->left;
        }
        }
        
        if ((targetptr->right != NULL) and (resptr->right ==NULL)){
            if (resptr!= targetptr->right){
            resptr-> right= targetptr->right;
        }
        }
       
        
        
    }
    else if (output.preptr!= NULL) {// target is leaf 
        if ((targetptr->data) < ((output.preptr)->data)){
            (output.preptr)->left= NULL;
            
        }
        else if ((targetptr->data) > ((output.preptr)->data)){
            (output.preptr)->right= NULL;
    }
    }
    if( preptr!=NULL){
        delete targetptr;
        targetptr = NULL;
        output.structptr = NULL;

        output.preptr= NULL;
        return;
    }
   
    
}





int main(){
    Node tree;
    tree.data= -1;
    tree.left= NULL;
    tree.right= NULL;

    bool run = true;
    bool adding = false;
    bool del = false;
    bool firstadd= true;
    while (run==true){
        std::cout<<"Enter \"Add\" to add data, \"Delete\" to delete data, \"Sort\" to view tree, \"q\" to quit. "<<std::endl;
        std::string mode;
        std::cin >> mode;
        if (mode=="Add"){
            adding= true;
        }
        else if (mode=="Delete"){
            del= true; // handle first pass
        }
        else if (mode=="Sort"){
            if (firstadd==true){
                std::cout<< "Tree is empty."<<std::endl;// handle first pass
            }
            else{
                sort(&tree);
            }
        }
        else if (mode=="q"){
            run= false;
            break;
        }
        while (adding==true){
            std::cout<< "Enter an integer, or enter a non-number key to do other things."<<std::endl;
            int n;
                
            std::cin >> n;
            if (std::cin.fail()) {
                std::cin.clear();   // clear the error flag
                std::cin.ignore();
                adding = false;  // ignore any remaining input
                break;
            }
            if (std::is_same<decltype(n), int>::value){
                if (firstadd==true){
                    add(&tree,n);
                    firstadd= false;
            }
                else {
                    add(&tree,n, false);

            }
             
            }
            
        }
        while (del==true){
            std::cout<< "Enter an integer, or enter a non-number key to do other things."<<std::endl;
            int n;
            std::cin >> n;

             if (std::cin.fail()) {
                std::cin.clear();   // clear the error flag
                std::cin.ignore();
                del = false;  // ignore any remaining input
                break;
            }
            if (std::is_same<decltype(n), int>::value){
                FinderStruct checker= finder(&tree, n, NULL, NULL, false, "target");
                if (checker.structptr == NULL){
                    std::cout<<"invalid deletion."<<std::endl;
                    continue;
                }
                if ((tree.right == NULL) and (tree.left == NULL)){ //the last element 
                    int dummy = n-1;
                    add(&tree, dummy, false);
                    deletion(&tree, n);
                    firstadd=true;
            }
            else {
                deletion(&tree, n);
            }

        }
        
    }
    }


    /*
    
    TESTING



    add(&tree,1);
    add(&tree,5, false);
    add(&tree,4, false);
    add(&tree,7, false);
    add(&tree,6, false);
    
    add(&tree,9, false);
    add(&tree,3, false);
    add(&tree,4, false);
    add(&tree,3, false);
    sort(&tree);
    std::cout<<"begins:"<<std::endl;
    
    Node* copy_5= tree.right;
    Node* copy_1= &tree;
    Node* copy_4= copy_5->left;
    Node* copy_5r= copy_5->right;

    copy_4->right= copy_5r;
    copy_1->right= copy_4;
    delete copy_5;
    copy_5= NULL;
    copy_5r= NULL; 
    sort(&tree);
    
    FinderStruct output;
    FinderStruct replacement;
    output= finder(&tree, 10, NULL, NULL, false, "target");
    //std::cout<< (output.structptr)->data<<std::endl;
    if (output.structptr==NULL){
         std::cout<<"empty";
    }
    else{
        std::cout<< (output.structptr)->data<<std::endl;
    }
    
    replacement = finder((output.structptr)->left, 6, NULL, NULL, false, "replacement");
    std::cout<< (replacement.structptr)->data<<std::endl;
    
   deletion(&tree, 4);
   std::cout<<"begins:"<<std::endl;
   if (tree.right != NULL){
       std::cout<<tree.right->data<<std::endl;
   }
   else{
       std::cout<<"it's empty"<<std::endl;
   }
    if ((tree.right)->right != NULL){
       std::cout<<((tree.right)->right)->data<<std::endl;
   }
   else{
       std::cout<<"it's empty"<<std::endl;
   }
   if ((tree.right)->left != NULL){
       std::cout<<((tree.right)->left)->data<<std::endl;
   }
   else{
       std::cout<<"it's empty"<<std::endl;
   }
   
    
   sort(&tree);
    */


    return 0;

};