pragma solidity >=0.4.22 <0.7.0;

contract ModifiedInPublicFuncContract {
    address owner; //@verifier fixed-after-init
    function somePublicFunc () public {
        somePrivateFunc();
    }
    function somePrivateFunc () private {
        changeOwner();
    }
    function changeOwner () private {
        owner = msg.sender;
    }
}