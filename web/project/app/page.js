import Image from "next/image";
import HeartBeating from "./components/heart";

function Hero() {
  return (
    <div className="mt-16 px-4 sm:px-16">
      <div className="relative px-4 sm:px-8 lg:px-12">
        <div className="mx-auto max-w-2xl lg:max-w-5xl">
          <div className="flex flex-col items-start md:flex-row md:items-center justify-between">
            <div className="md:w-2/3">
              <h1 className="text-4xl font-bold tracking-tight text-stone-800 dark:text-stone-100 sm:text-5xl">
                I&apos;m Homer Simpson. An engineer, programmer, and full-stack
                developer based in Springfield, USA.
              </h1>
              <div className="mt-6 space-y-7 text-base text-stone-600 dark:text-stone-400">
                <p>
                  Hey there, I&apos;m Homer Simpson, a freelance web and app
                  developer specializing in the MERN Stack and Flutter. But
                  I&apos;m not just another developer—I blend technical skills
                  with a dash of my unique charm. Creating smooth digital
                  experiences is my jam, and I&apos;m always ready to tackle the
                  next tech trend to stay on top.
                </p>
                <p>
                  When I&apos;m not knee-deep in code, you&apos;ll find me
                  enjoying donuts, rocking out to some tunes, or enjoying a nice
                  cold Duff beer. Oh, and I never skip the gym (unless
                  there&apos;s pie involved)! Join me in the quest where tech
                  meets personality—let&apos;s make something epic together!
                </p>
              </div>
            </div>
            <Image
              src="https://upload.wikimedia.org/wikipedia/en/0/02/Homer_Simpson_2006.png"
              alt="Homer Simpson"
              width={220}
              height={220}
              className="max-w-[10rem] py-3 px-2.5 lg:max-w-none order-first lg:order-last"
            />
          </div>
        </div>
      </div>
    </div>
  );
}

function Projects() {
  const projects = [
    {
      title: "Donut Finder App",
      description:
        "A Flutter-based app that helps users locate the best donut shops in Springfield.",
      iconSVG: (
        <svg
          xmlns="http://www.w3.org/2000/svg"
          width="42"
          height="42"
          viewBox="0 0 24 24"
        >
          <g fill="none">
            <path
              fill="#631134"
              d="M21.407 14.261a4.6 4.6 0 0 0 0-4.522l-2.784-4.923a4.41 4.41 0 0 0-3.834-2.262H9.211a4.41 4.41 0 0 0-3.834 2.262L2.593 9.739a4.6 4.6 0 0 0 0 4.522l2.784 4.923a4.41 4.41 0 0 0 3.834 2.261h5.578a4.41 4.41 0 0 0 3.834-2.26zm-6.773-2.844a1.24 1.24 0 0 1 0 1.166l-.85 1.612a1.06 1.06 0 0 1-.934.583h-1.7c-.389 0-.74-.222-.934-.583l-.85-1.612a1.26 1.26 0 0 1 0-1.166l.85-1.612a1.07 1.07 0 0 1 .934-.583h1.7c.389 0 .739.222.934.583z"
            />
            <path
              fill="#E8B4D0"
              fill-rule="evenodd"
              d="M20.428 13.756a3.58 3.58 0 0 0 0-3.512l-2.722-4.823a3.42 3.42 0 0 0-2.984-1.755H9.277A3.42 3.42 0 0 0 6.304 5.42l-2.728 4.823a3.58 3.58 0 0 0 0 3.512L6.3 18.579a3.42 3.42 0 0 0 2.978 1.755h5.456a3.42 3.42 0 0 0 2.973-1.755l2.728-4.823zm-5.09-.761a2.04 2.04 0 0 0 0-1.99l-.833-1.46a1.93 1.93 0 0 0-1.678-.995h-1.655c-.695 0-1.334.377-1.684.994L8.666 11a2.02 2.02 0 0 0 0 1.989l.833 1.345a1.93 1.93 0 0 0 1.667 1h1.656c.694 0 1.333-.378 1.683-.995L15.333 13z"
              clip-rule="evenodd"
            />
            <path
              fill="#DD679F"
              d="M20.429 10.244a3.58 3.58 0 0 1 0 3.512l-2.723 4.823a3.42 3.42 0 0 1-2.983 1.755H9.277a3.43 3.43 0 0 1-2.967-1.739l-2.255-3.984a3.58 3.58 0 0 1 0-3.511l2.722-4.567a3.42 3.42 0 0 1 2.984-1.756h5.59c1.222 0 2.344.667 2.96 1.739l2.123 3.723zm-10.24 5.229a1.79 1.79 0 0 0 1.6.972h1.522c.695 0 1.334-.378 1.684-.995l.828-1.605a2.03 2.03 0 0 0 0-1.984c-.428-.75-.84-1.484-1.312-2.2a1.93 1.93 0 0 0-1.683-.995h-1.656c-.694 0-1.333.378-1.683.995L8.666 11a2.02 2.02 0 0 0 0 1.989c.445.772 1.09 1.706 1.528 2.478z"
            />
            <path
              fill="#000"
              d="M2.771 8.683c-.333-.445-.278-1.095.144-1.456a.934.934 0 0 1 1.367.156l1.39 1.822c.333.445.277 1.095-.145 1.456a.935.935 0 0 1-1.367-.156z"
            />
            <path
              fill="#6CBDDE"
              d="M2.966 8.516a.794.794 0 0 1 .11-1.083a.695.695 0 0 1 1.012.11l1.39 1.829a.794.794 0 0 1-.112 1.083a.69.69 0 0 1-1.011-.11z"
            />
            <path
              fill="#000"
              d="M12.05 19.629a1.11 1.11 0 0 1-.523-1.423a.99.99 0 0 1 1.334-.555l1.31.61a1.11 1.11 0 0 1 .523 1.423a.99.99 0 0 1-1.333.556z"
            />
            <path
              fill="#6CBDDE"
              d="M12.155 19.373c-.383-.178-.555-.65-.389-1.056c.167-.41.612-.594.995-.416l1.306.61c.383.184.555.656.389 1.062c-.167.411-.612.595-.995.417l-1.306-.611z"
            />
            <path
              fill="#000"
              d="M18.134 14.806c-.111-.495.178-.995.65-1.111c.472-.123.945.183 1.056.678l.472 2.044c.111.495-.178.995-.65 1.111c-.472.123-.945-.183-1.056-.677z"
            />
            <path
              fill="#DC3C46"
              d="M18.356 14.75a.684.684 0 0 1 .478-.828a.65.65 0 0 1 .789.506l.467 2.045a.684.684 0 0 1-.478.828a.647.647 0 0 1-.79-.506z"
            />
            <path
              fill="#000"
              d="M16.745 3.732a.99.99 0 0 1 1.322-.533c.506.228.739.839.517 1.367l-.778 1.811a.99.99 0 0 1-1.317.533a1.05 1.05 0 0 1-.517-1.366l.778-1.812z"
            />
            <path
              fill="#F1DF73"
              d="M16.978 3.832a.736.736 0 0 1 .984-.389a.776.776 0 0 1 .389 1.012l-.778 1.817a.744.744 0 0 1-.984.4a.78.78 0 0 1-.383-1.017l.778-1.817z"
            />
            <path
              fill="#000"
              d="M10.11 5.366a1.056 1.056 0 0 1 1.29.722a1.027 1.027 0 0 1-.745 1.261l-.666.167a1.056 1.056 0 0 1-1.284-.722a1.015 1.015 0 0 1 .744-1.256l.662-.167z"
            />
            <path
              fill="#F0EFF4"
              d="M10.177 5.621a.784.784 0 0 1 .961.54a.76.76 0 0 1-.555.933l-.662.172a.787.787 0 0 1-.96-.539a.764.764 0 0 1 .555-.933l.667-.173z"
            />
            <path
              fill="#000"
              d="M16.367 8.889a1.054 1.054 0 0 1 1.534.255c.355.522.25 1.25-.245 1.634l-.578.444a1.06 1.06 0 0 1-1.226.051a1.21 1.21 0 0 1-.062-1.94z"
            />
            <path
              fill="#F0EFF4"
              d="M16.528 9.127a.793.793 0 0 1 1.144.195a.9.9 0 0 1-.177 1.211l-.578.445a.787.787 0 0 1-1.145-.19a.9.9 0 0 1 .178-1.21l.578-.445z"
            />
            <path
              fill="#000"
              d="M7.66 15.456a1.07 1.07 0 0 1 1.445.461a1.086 1.086 0 0 1-.461 1.45l-1.195.623a1.07 1.07 0 0 1-1.444-.462a1.083 1.083 0 0 1 .46-1.45z"
            />
            <path
              fill="#F1DF73"
              d="M7.788 15.7a.787.787 0 0 1 1.073.345c.2.389.05.872-.345 1.078l-1.194.622a.787.787 0 0 1-1.073-.344a.803.803 0 0 1 .345-1.078z"
            />
          </g>
        </svg>
      ),
    },
    {
      title: "Duff Beer Tracker",
      description:
        "A MERN Stack web app that tracks Duff beer availability and specials across local bars.",
      iconSVG: (
        <svg
          xmlns="http://www.w3.org/2000/svg"

          width="32"
          height="32"
          viewBox="0 0 36 36"
        >
          <path
            fill="#FFAC33"
            d="M31 5.718h-6v4h4s2 0 2 2v12c0 2-2 2-2 2h-4v4h6c2.206 0 4-1.794 4-4v-16c0-2.206-1.794-4-4-4"
          />
          <path fill="#FFCC4D" d="M27 6H3v26a4 4 0 0 0 4 4h16a4 4 0 0 0 4-4z" />
          <path
            fill="#F4900C"
            d="M8.5 32a1 1 0 0 1-1-1V15a1 1 0 0 1 2 0v16a1 1 0 0 1-1 1m6.5 0a1 1 0 0 1-1-1V15a1 1 0 0 1 2 0v16a1 1 0 0 1-1 1m6.5 0a1 1 0 0 1-1-1V15a1 1 0 1 1 2 0v16a1 1 0 0 1-1 1"
          />
          <path
            fill="#FFAC33"
            d="M3 5v7.445c.59.344 1.268.555 2 .555a4 4 0 0 0 3.701-2.491c.35.302.801.491 1.299.491c.677 0 1.273-.338 1.635-.853A3.99 3.99 0 0 0 15 12a3.98 3.98 0 0 0 3.176-1.593A2.5 2.5 0 0 0 20.5 12c.949 0 1.765-.535 2.188-1.314l.147-.361a3.46 3.46 0 0 0 1.665.439c.981 0 1.865-.406 2.5-1.056V5z"
          />
          <path
            fill="#EEE"
            d="M24 0H4a3 3 0 0 0-3 3v4a4 4 0 0 0 7.701 1.509C9.051 8.811 9.502 9 10 9c.677 0 1.273-.338 1.635-.853A3.99 3.99 0 0 0 15 10a3.98 3.98 0 0 0 3.176-1.593A2.5 2.5 0 0 0 20.5 10c.949 0 1.765-.535 2.188-1.314c.398.195.839.314 1.312.314a3 3 0 0 0 3-3V3a3 3 0 0 0-3-3"
          />
        </svg>
      ),
    },
    {
      title: "Springfield Gym Scheduler",
      description:
        "A fitness app built with React, allowing users to schedule gym sessions and track workouts.",
      iconSVG: (
        <svg
          xmlns="http://www.w3.org/2000/svg"
          width="32"
          height="32"
          viewBox="0 0 14 14"
        >
          <g
            fill="none"
            stroke="#888888"
            stroke-linecap="round"
            stroke-linejoin="round"
          >
            <rect width="4" height="6" x=".5" y="4" rx="1" />
            <rect width="4" height="6" x="9.5" y="4" rx="1" />
            <path d="M4.5 7h5" />
          </g>
        </svg>
      ),
    },
  ];

  return (
    <div className="mt-16 px-4 sm:mt-32 sm:px-16">
      <div className="relative px-4 sm:px-8 lg:px-12">
        <div className="mx-auto max-w-2xl space-y-10 lg:max-w-5xl">
          <h1 className="text-4xl font-bold tracking-tight text-stone-800 dark:text-stone-100 sm:text-5xl">
            Projects
          </h1>
          <div className="grid grid-cols-1 gap-x-12 gap-y-16 sm:grid-cols-2 lg:grid-cols-3">
            {projects.map((project) => (
              <div
                key={project.title}
                className="group relative flex flex-col gap-5 overflow-hidden rounded-lg border border-stone-200 p-6 shadow-sm transition-shadow duration-300 ease-in-out hover:bg-stone-50 hover:shadow-lg dark:border-stone-700 dark:hover:bg-stone-800"
              >
                {project.iconSVG}
                <p className="text-xl font-semibold text-stone-800 dark:text-stone-100">
                  {project.title}
                </p>
                <p className="text-base text-stone-600 dark:text-stone-400">
                  {project.description}
                </p>
              </div>
            ))}
          </div>
        </div>
      </div>
    </div>
  );
}

function LikeMe() {
  return (
    <div className="mt-16 px-4 sm:mt-32 sm:px-16">
      <div className="relative px-4 sm:px-8 lg:px-12">
        <div className="mx-auto max-w-2xl space-y-10 lg:max-w-5xl">
          <h1 className="text-4xl font-bold tracking-tight text-stone-800 dark:text-stone-100 sm:text-5xl">
            How did you like my portfolio?
          </h1>
          <HeartBeating />
        </div>
      </div>
    </div>
  );
}

export default function Home() {
  return (
    <>
      <div className="fixed inset-0 flex justify-center sm:px-8">
        <div className="flex w-full max-w-7xl lg:px-8">
          <div className="w-full rounded-lg bg-white ring-2 ring-stone-100 dark:bg-stone-900 dark:ring-stone-300/20"></div>
        </div>
      </div>
      <Hero />
      <Projects />
      <LikeMe />
    </>
  );
}
