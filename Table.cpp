#include "Table.h"

// Task 9
Table::Table()
{
    totalColumns = 0;
    columnHead = nullptr;
}

// Task 10
Table::~Table()
{
   if(columnHead == nullptr)
        return;
    else{
        Column* current = columnHead;
        while(current->next != nullptr){
            current = current->next;
            delete current->prev;
        }
        delete current;
        current = nullptr;
    }
}

// Task 11
Column* Table::findColumn(int colNum) const
{
    if(colNum < 0)
        return nullptr;
    
    if(colNum >= totalColumns)
        return nullptr;
    else{     // colNum < totalColumns
        Column* current = columnHead;
        for(int i = 0; i < colNum; i++)
            current = current->next;  
        return current;
    }
}

// Task 12
void Table::copyInsertColumn(int fromColNum, int toColNum)
{
   
    Column* from_column = findColumn(fromColNum);

    if(toColNum >= totalColumns){       // column to insert does not exist  
        if(from_column == nullptr)     //case 2 (from column does not exist so empty)
            return;
        else if(from_column->getRowHead() == nullptr)      // also case 2 ( exists but empty)
            return;
        else{                      //case 4  (from column has content)
            Column* last_one = findColumn(totalColumns-1);
            while(totalColumns < toColNum){       // add necessary columns
                last_one->next = new Column(last_one);
                last_one = last_one->next;
                totalColumns++;
            }
            last_one->next = new Column(*from_column);
            last_one->next->next = nullptr;
            totalColumns++;
            return;                 
        }
    }

    if(toColNum == 0){  // insert into head column
        if(from_column == nullptr || from_column->getRowHead() == nullptr){
            columnHead->prev = new Column();
            columnHead->prev->next = columnHead;
            columnHead = columnHead->prev;
            totalColumns++;
            return;
        }
        else{
            columnHead->prev = new Column(*from_column);
            columnHead->prev->next = columnHead;
            columnHead = columnHead->prev;
            totalColumns++;
            return;
        }
    }

    if(toColNum < totalColumns){        // column to insert exist in middle
        if(from_column == nullptr || from_column->getRowHead() == nullptr){
            Column* new_one = new Column();
            Column* before_to_column = findColumn(toColNum-1);
            new_one->next = before_to_column->next;
            before_to_column->next = new_one;
            new_one->next->prev = new_one;
            new_one->prev = before_to_column;
            totalColumns++;
            return;
        }
        else{
            Column* new_one = new Column(*from_column);
            Column* before_to_column = findColumn(toColNum-1);
            new_one->next = before_to_column->next;
            before_to_column->next = new_one;
            new_one->next->prev = new_one;
            new_one->prev = before_to_column;
            totalColumns++;
            return;
        }
    }

}

// Task 13
void Table::deleteColumn(int colNum)
{
     if(colNum >= totalColumns)  //Column does not exist
        return;

    if(colNum == 0){          // column head
        Column* current = columnHead;
        columnHead =current->next;
        delete current;
        columnHead->prev = nullptr;
        totalColumns--;
        return;
    }
    if(colNum < totalColumns - 1 && colNum != 0){ // middle of column
        Column* current = findColumn(colNum);
        current->prev->next = current->next;
        current->next->prev = current->prev;
        delete current;
        current = nullptr;
        totalColumns--;
        return;
    }
    if(colNum = totalColumns - 1){ // last column
        Column* current = findColumn(colNum-1);
        delete current->next;
        current->next = nullptr;
        totalColumns--;
        while(current->getRowHead() == nullptr){  //keep deleting until column has smth(not nullptr)
            current = current->prev;
            delete current->next;
            current->next = nullptr;
            totalColumns--;
            if(current == columnHead)
                break;
        }
    }


}

// Task 14
Cell *Table::findCell(int colNum, int rowNum) const
{   
    Column* current = findColumn(colNum);
    if(current == nullptr) // column dont exist
        return nullptr;

    if(current->findCell(rowNum) == nullptr)  // row doesnt exist
        return nullptr;  

    return current->findCell(rowNum);
    
}

// Task 15
void Table::modifyCell(int colNum, int rowNum, const string &value)
{
    Cell* current_cell = findCell(colNum,rowNum);
    if(current_cell != nullptr)     // cell exist
        current_cell->value = value;
    else{       
        Column* current_col;                        
        if(colNum < totalColumns){   // column exist
            current_col = findColumn(colNum);
            current_col->modifyCell(rowNum,value);
        }
        else{
            if(columnHead == nullptr){
                    columnHead = new Column();
                    current_col = columnHead;
                    totalColumns++;
                }
            Column* current_col = findColumn(totalColumns-1);  // find last column
            while(colNum >= totalColumns){
                current_col->next = new Column(current_col);
                current_col = current_col->next;
                totalColumns++;
            }
            current_col->next = nullptr;
            current_col->modifyCell(rowNum,value);
        }
    } 
}

// Task 16
void Table::clearCell(int colNum, int rowNum)
{
    Cell* current_cell = findCell(colNum,rowNum);
        
    if(current_cell == nullptr){    // cell does not exist
        return;
    }

    Column* current_col = findColumn(colNum); 
    current_col->clearCell(rowNum); 


    if(colNum == totalColumns-1 ){    // last column
        while(current_col->getRowHead() == nullptr){  // column empty 
            if(current_col == columnHead){
                if(current_col->getRowHead() == nullptr){
                    totalColumns--;
                    delete current_col;
                    columnHead = nullptr;
                    return;
                }
            }
            current_col = current_col->prev;
            delete current_col->next;
            current_col->next = nullptr;
            totalColumns--;
                
        }
            
    }
}

// ---------------------- provided functions: DO NOT MODIFY --------------------------
void Table::printTable() const
{

    // find the max number of rows
    int maxRows = 0;
    Column *currCol = columnHead;
    while (currCol != nullptr)
    {
        if (currCol->getTotalRows() > maxRows)
        {
            maxRows = currCol->getTotalRows();
        }
        currCol = currCol->next;
    }

    cout << "totalColumns: " << totalColumns << "\t ";
    cout << "maxRows: " << maxRows << endl;


    // string styles
    string line(12, '-');
    string doubleline(12, '=');
    string space(12, ' ');
    string headerline((totalColumns+1)*12, '=');


    // print table table header
    cout << headerline << endl;
    cout << " " << std::setw(10) << "" << "|";
    for (int i = 0; i < totalColumns; ++i)
    {
        cout<< "|" << std::setw(10) << "column "+to_string(i)+ " " << "|";
    }
    cout << endl;
    cout << headerline << endl;
    

    // print table body (row by row)
    string hline;
    for (int i = 0; i < maxRows; ++i)
    {
        hline = doubleline;    
        cout<< " " << std::setw(10) << "row "+to_string(i) + "  "<< " ";


        currCol = columnHead;

        while (currCol != nullptr)
        {
            Cell *currCell = currCol->findCell(i);
            if (currCell == nullptr)
            {
                hline += space;
                cout << " "<< std::setw(10) <<"" << " ";
            }
            else
            {
                hline += line;
                cout << "|" << std::setw(10) << currCell->value << "|";
            }
            currCol = currCol->next;
        }
        cout << endl;

        cout << hline << endl;
    }

    cout << endl;
    return;

}
