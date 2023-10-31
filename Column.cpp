#include "Column.h"

// Task 1
Column::Column()
{
    totalRows = 0;
    rowHead = nullptr;
    prev = nullptr;
    next = nullptr;
}

// Task 2
Column::Column(Column *prev): prev(prev) {
    totalRows = 0;
    rowHead = nullptr;
    next = nullptr;
}

// Task 3
Column::Column(const Column &c)
{
    totalRows = c.totalRows;
    prev = nullptr;
    next = nullptr;

    if(c.totalRows == 0)   // column has no cells
        rowHead = nullptr;

    if(totalRows != 0){    
        rowHead = new Cell;
        rowHead->prev = nullptr;
        rowHead->next = nullptr;
        rowHead->value = c.rowHead->value;  // copy row head

        Cell* c_current = c.rowHead;
        Cell* new_current = rowHead;
        while(c_current->next != nullptr){  // keep copying until no more cells
            new_current->next = new Cell;
            new_current->next->value = c_current->next->value;
            new_current->next->prev = new_current;
            new_current->next->next = nullptr;
            c_current = c_current->next;
            new_current = new_current->next;
        }    
    }
}

// Task 4
Column::~Column()
{
    if(rowHead != nullptr){
        Cell* current = rowHead;
        while(current->next != nullptr){
            current = current->next;
            delete current->prev;
        }
        delete current;
        current = nullptr;
    }

}

// Task 5
Cell *Column::findCell(int rowNum)
{   
    if(rowNum < 0)
        return nullptr; 
    if(rowNum >= totalRows)
        return nullptr;
    
    else{         // rowNum < totalRows
        Cell* current = rowHead;
        for(int i = 0; i < rowNum; i++)
            current = current->next;
        return current;
    }

}

// Task 6
void Column::modifyCell(int rowNum, const string &value)
{
    if(rowNum < 0)
        return;
    Cell* current = findCell(rowNum);
    if(current != nullptr){        // row exists
        current->value = value; 
        return;
    }
    else{   // row does not exists (current == nullptr)
        if(totalRows == 0){  // no cell in the column  
        current = new Cell;
        current->prev = nullptr;
        current->next = nullptr;
        current->value = "";
        rowHead = current;
        totalRows++;
        }
        current = findCell(totalRows-1);  // find last cell in column
        while(totalRows <= rowNum){   // create until row rowNum
            current->next = new Cell;
            current->next->value ="";
            current->next->prev = current;
            current->next->next = nullptr;
            current = current->next;
            totalRows++;
        }
        current->value = value;
        return;
    }
}
// Task 7
void Column::clearCell(int rowNum)
{
    if(rowNum < 0)
        return;
    if(rowNum >= totalRows) // row does not exist
        return;
    
    Cell* current = findCell(rowNum); 

    if(rowNum < totalRows - 1){ //middle cell
        current->value = "";
        return;
    }

    if(rowNum == totalRows - 1){  // last cell
        if(current->prev == nullptr){   // head cell
            clearAllCells();
            return;
        }
        current = current->prev;
        delete current->next;
        current->next = nullptr;
        totalRows--;
        while(current->value == ""){
            if(current == rowHead){
                clearAllCells();
                return;
            }
            current = current->prev;
            delete current->next;
            current->next = nullptr;
            totalRows--;
        }
        

    }
    
}
// Task 8
void Column::clearAllCells()
{
    if(totalRows > 0){
        Cell* current = rowHead;
        while(current->next != nullptr){
            current = current->next;
            delete current->prev;
        }
        delete current;
        current = nullptr;
    }
    rowHead = nullptr;
    totalRows = 0;
}

// ---------------------- provided functions: DO NOT MODIFY --------------------------
void Column::printColumn() const
{
    // string styles
    string line(12, '-');
    string doubleline(12, '=');
    string space(12, ' ');



    cout << "totalRows: " << totalRows << endl;

    // table header
    cout << doubleline + doubleline << endl;
    cout << " " << std::setw(10) << "" << " ";
    cout << "|" << std::setw(10)  << "column " << "|" <<endl;   
    cout << doubleline + doubleline << endl;

    // table body (row by row)
    Cell* current = rowHead;
    for (int i =0 ; i < totalRows; ++i){
        cout << " " << std::setw(10) << "row " + to_string(i) + " " << " " ;
        cout << "|" << std::setw(10) << current->value << "|" << endl;
        current = current->next;
        cout << doubleline + line << endl;
    }

    cout << endl;

}
