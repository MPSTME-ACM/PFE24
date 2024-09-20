"use client";

import { useState } from "react";
import { Heart } from "lucide-react";

export default function HeartBeating() {
  const [count, setCount] = useState(0);
  const [isBeating, setIsBeating] = useState(false);

  const handleClick = () => {
    setCount(count + 1);
    setIsBeating(true);
    setTimeout(() => setIsBeating(false), 300); // Reset beating after 300ms
  };

  return (
    <div className="flex flex-row items-center justify-start gap-5">
      <button
        onClick={handleClick}
        className="flex flex-row items-center justify-center p-4 bg-white dark:bg-black rounded-full shadow-lg transition-transform duration-300 hover:scale-110 focus:outline-none"
        aria-label="Like"
      >
        <Heart
          size={18}
          className={`text-red-500 transition-transform duration-300 ${
            isBeating ? "scale-125" : "scale-100"
          }`}
        />
      </button>
      <p className=" text-base text-stone-600 dark:text-stone-400">{count}</p>{" "}
    </div>
  );
}
